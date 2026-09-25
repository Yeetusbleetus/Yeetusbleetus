"""Build a battery-focused read-only scan list from data/bmw_ev_dids.json.

Output: data/scan_reads.csv + data/scan_reads.json — every read-only request (UDS 0x22 DIDs, read-only
0x31 routines, and 0x31 0x03 'request results' for test routines) per ECU type, merged across generations.
"""
import json, os, re, csv
from collections import OrderedDict

H = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
dids = json.load(open(H + '/data/bmw_ev_dids.json'))['dids']

SIZES = {'signed char': 1, 'unsigned char': 1, 'char': 1, 'signed int': 2, 'unsigned int': 2, 'int': 2,
         'long': 4, 'signed long': 4, 'unsigned long': 4, 'float': 4, 'real': 4, 'motorola float': 4,
         'intel float': 4, 'double': 8}

BATTERY_ECUS = {'SME', 'SMES1', 'SMES2'}
# non-battery ECUs: keep a DID only if it is about the HV battery, charging, isolation or the 12V battery
KEYWORDS = re.compile(
    r'BATT|HVS|HV_|_HV|HV-|SOC|ZELL|SPEICHER|LADE|LADUNG|ISO|SCHUETZ|SCHÜTZ|IBS|SME|KL30|DCDC|'
    r'battery|high.voltage|state of charge|cell|charg|insulation|isolation|contactor|storage', re.I)

# 0x31 routines that only read data (argument = index into cells/modules/records/histograms)
READ_ROUTINES = {
    'SME': {'0xAD6C', '0xAD6D', '0xAD6E', '0xAD6F', '0xAD70', '0xAD71', '0xAD74', '0xAD76', '0xAD77', '0xAD78',
            '0xAD79', '0xAD7C', '0xAD7D'},
    'EME': {'0xADFC', '0xAF42', '0xADF9'},  # charge-history records, charger histograms, DC/DC histograms
    'SLE': {'0xAF41'},                      # charger temperature histograms
    'EDME': {'0xADFD'},                     # 12V top-up charge history records
}
# test/actuation routines on battery ECUs whose last result can be fetched with 31 03 without starting them
RESULTS_ONLY = {'SME': {'0xAD61', '0xAD66', '0xAD6A', '0xAD6B', '0xAD73', '0xAD62', '0xAD60'},
                'SMES1': {'0xAD61'}, 'SMES2': {'0xAD61'}}

# index arguments: how to sweep them. Known counts per pack; otherwise sweep and stop on NRC 0x31.
SWEEP = {
    'NR_ZELLE': dict(start=1, end=255, note='i3: cells 1..96 (1-based, confirmed by Battery-Emulator). Stop on repeated 7F 31 31'),
    'NR_MODUL': dict(start=0, end=32, note='i3: 8 modules. Sweep, keep positive responses'),
    'NR_CSC': dict(start=0, end=32, note='one CSC per module'),
    'SATZ': dict(start=0, end=32, note='history record number'),
    'HISTOGRAMM_NR': dict(start=0, end=32, note='histogram number'),
    'HISTOGRAMM_SLE_NR': dict(start=0, end=32, note='charger histogram number'),
    'TEMPERATUR_BEREICH': dict(start=0, end=16, note='temperature range selector'),
}

# diagnostic addresses (ISO-TP extended addressing: tester 0xF1 -> CAN 0x600+addr... resp 0x600+addr w/ ext addr 0xF1)
ADDR = {'SME': '0x07', 'EME': '0x1A', 'KLE': '0x15', 'LIM': '0x14', 'IHX': '0x78', 'EDME': '0x12'}


def size_of(r):
    t = r['type']
    if t.upper() == 'BITFIELD':
        return None
    m = re.match(r'(?:data|string)\[(\d+)\]', t)
    return int(m.group(1)) if m else SIZES.get(t)


def resp_len(res):
    """Expected payload length after the DID (None if not computable)."""
    if not res or any(r['routine_phase'] for r in res):
        return None
    last = res[-1]
    if last['offset'] == '':
        return None
    s = size_of(last)
    if s is None and last.get('bits'):
        s = 1
    return None if s is None else last['offset'] + s


def arg_len(a):
    return size_of(a) or 1


out = OrderedDict()
for d in dids:
    ecu, svc, did = d['ecu'], d['service'], d['did']
    readable = svc.split(';')[0] == '22' or '22' in svc.split(';')
    kind = None
    if readable:
        if ecu in BATTERY_ECUS or KEYWORDS.search(d['name'] + ' ' + d['info'] + ' ' + d['info_en']):
            kind = 'did'
    elif svc.startswith('31'):
        if did in READ_ROUTINES.get(ecu, ()):
            kind = 'routine_read'
        elif did in RESULTS_ONLY.get(ecu, ()):
            kind = 'routine_results'
    if not kind:
        continue
    key = (ecu, kind, did)
    e = out.get(key)
    if not e:
        hexid = did[2:]
        idb = f'{hexid[:2]} {hexid[2:]}'
        args = [a for a in d['args'] if 'start' in a['routine_phase']] if kind == 'routine_read' else []
        sweep = []
        for a in args:
            sp = SWEEP.get(a['name'], dict(start=0, end=16, note='unknown selector - sweep small range'))
            sweep.append({'arg': a['name'], 'type': a['type'], 'bytes': arg_len(a), **sp})
        if kind == 'did':
            req = f'22 {idb}'
        elif kind == 'routine_read':
            req = f'31 01 {idb}' + ''.join(' <' + s['arg'] + (f":{s['bytes']}B" if s['bytes'] > 1 else '') + '>' for s in sweep)
            followup = f'31 03 {idb}'
        else:
            req = f'31 03 {idb}'
        e = out[key] = {
            'ecu': ecu, 'diag_addr_i3': ADDR.get(ecu, ''), 'kind': kind, 'id': did, 'request': req,
            'sweep': sweep, 'names': [], 'description_en': d['info_en'], 'description_de': d['info'],
            'expected_payload_len': resp_len(d['results']) if kind == 'did' else None,
            'n_fields': len(d['results']), 'vehicles': [],
            'relevance': 'battery' if ecu in BATTERY_ECUS else 'hv/charging/12v', 'source': 'sgbd',
        }
        if kind == 'routine_read':
            e['followup'] = followup
    if d['name'] not in e['names']:
        e['names'].append(d['name'])
    if d['vehicle'] not in e['vehicles']:
        e['vehicles'].append(d['vehicle'])
    # conflicting layouts across generations: keep the shortest-known expected length as a hint only
    if kind == 'did':
        l = resp_len(d['results'])
        if l is not None and e['expected_payload_len'] not in (None, l):
            e['layout_differs_between_generations'] = True

# community-documented reads for generations without public SGBDs
comm = json.load(open(H + '/data/community_dids.json'))
for c in comm['dids']:
    req = c['request']
    if req.startswith('31 01'):   # i3 two-step cell read is already covered by the SGBD routine entry
        continue
    parts = req.split()
    did = '0x' + ''.join(parts[-2:]).upper()
    kind = 'did' if parts[0] == '22' else 'routine_results'
    match = next((e for e in out.values() if e['ecu'] == c['ecu'] and e['kind'] == kind and e['id'] == did), None)
    if match:
        match['vehicles'].append(c['family'] + ' (community)')
        match.setdefault('community_layout', []).append({'family': c['family'], 'layout': c['layout'], 'source': c['source']})
        continue
    out[(c['ecu'], kind, did, c['family'])] = {
        'ecu': c['ecu'], 'diag_addr_i3': c['addr'], 'kind': kind, 'id': did, 'request': req, 'sweep': [],
        'names': [c['name']], 'description_en': c['name'], 'description_de': '', 'expected_payload_len': None,
        'n_fields': 0, 'vehicles': [c['family'] + ' (community)'], 'relevance': 'battery', 'source': 'community',
        'community_layout': [{'family': c['family'], 'layout': c['layout'], 'source': c['source']}]}
# merge duplicate community rows (same DID seen for Gen4 and Gen5)
merged = OrderedDict()
for k, e in out.items():
    kk = (e['ecu'], e['kind'], e['id'])
    if kk in merged:
        m = merged[kk]
        m['vehicles'] += [v for v in e['vehicles'] if v not in m['vehicles']]
        m['names'] += [n for n in e['names'] if n not in m['names']]
        m.setdefault('community_layout', []).extend(e.get('community_layout', []))
    else:
        merged[kk] = e
out = merged

DISCOVERY = {
    'purpose': 'Find what an uncovered car actually supports. Everything here is read-only. Save every response.',
    'step_1_find_ecus': {
        'how': 'For each diagnostic address 0x00..0xEF send the probe; any reply (positive or 7F) means an ECU lives there.',
        'probe': ['22 F1 90', '22 F1 86', '3E 00'],
        'known_battery_addresses': {'SME (Gen3, Gen4 PHEV, Gen5 iX/i4)': '0x07'},
        'timeout_ms': 250,
    },
    'step_2_did_sweep': {
        'how': 'Send 22 <hi> <lo> for every DID to the battery ECU (0x07) and any other HV ECU found. Priority ranges first.',
        'priority_ranges': [['0xDD00', '0xDFFF'], ['0xE400', '0xE6FF'], ['0x6300', '0x65FF'], ['0xD400', '0xD6FF'],
                            ['0xA800', '0xAFFF'], ['0x4000', '0x41FF'], ['0x1000', '0x10FF'], ['0xF100', '0xF1FF']],
        'full_range': ['0x0100', '0xFEFF'],
        'responses': {
            '62 ...': 'supported - save payload',
            '7F 22 31': 'requestOutOfRange - DID not supported (the common case)',
            '7F 22 7F / 7F 22 7E': 'supported but not in this session - retry in extended session (10 03)',
            '7F 22 33': 'securityAccessDenied - exists but locked; record, do not attempt unlock',
            '7F 22 22': 'conditionsNotCorrect - exists; retry later (e.g. ignition on / HV active)',
            '7F 22 78': 'responsePending - keep waiting (up to ~5 s)',
            '7F 22 13': 'incorrect length - exists, may need a parameter; record',
        },
        'pace': 'about 10-20 ms per request; full range takes ~15-20 min. Send 3E 00 every 2 s.',
    },
    'step_3_routine_id_sweep_optional': {
        'how': 'Send ONLY 31 03 <hi> <lo> (request routine results) over 0x0000..0xFFFF. This never starts a routine. '
               'A routine that exists but was not run usually answers 7F 31 24 (requestSequenceError) instead of 7F 31 31.',
        'never': 'Do not send 31 01 (start) or 31 02 (stop) to discovered IDs: routines open contactors, start tests or reset data.',
    },
    'step_4_dtcs': {'requests': ['19 02 FF', '19 0A'], 'note': 'Read stored / supported DTCs (read-only).'},
}

rows = sorted(out.values(), key=lambda e: (e['ecu'] not in BATTERY_ECUS, e['ecu'], e['kind'], e['id']))
json.dump({'note': 'Read-only UDS requests for BMW EV/hybrid HV-battery related ECUs, merged across generations. '
                   'Send each to the ECU, save the raw response bytes (including negative responses).',
           'discovery': DISCOVERY, 'requests': rows}, open(H + '/data/scan_reads.json', 'w'), ensure_ascii=False, indent=1)
with open(H + '/data/scan_reads.csv', 'w', newline='') as f:
    w = csv.writer(f)
    w.writerow(['ecu', 'diag_addr_i3', 'kind', 'id', 'request', 'followup', 'sweep', 'names', 'expected_payload_len',
                'layout_differs', 'vehicles', 'relevance', 'description_en'])
    for e in rows:
        w.writerow([e['ecu'], e['diag_addr_i3'], e['kind'], e['id'], e['request'], e.get('followup', ''),
                    '; '.join(f"{s['arg']} {s['start']}..{s['end']}" for s in e['sweep']), ' / '.join(e['names']),
                    e['expected_payload_len'] if e['expected_payload_len'] is not None else '',
                    'yes' if e.get('layout_differs_between_generations') else '', ' | '.join(e['vehicles']),
                    e['relevance'], e['description_en'] + (' | community layout: ' + '; '.join(
                        f"{c['family']}: {c['layout']}" for c in e.get('community_layout', [])) if e.get('community_layout') else '')])

from collections import Counter
print(len(rows), 'requests')
print(Counter((e['ecu'], e['kind']) for e in rows))
