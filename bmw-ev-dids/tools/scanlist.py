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
    'NR_ZELLE': dict(start=0, end=255, note='i3: 96 cells. Numbering base (0/1) not given in SGBD - sweep and keep all positive responses'),
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
        else:
            req = f'31 03 {idb}'
        e = out[key] = {
            'ecu': ecu, 'diag_addr_i3': ADDR.get(ecu, ''), 'kind': kind, 'id': did, 'request': req,
            'sweep': sweep, 'names': [], 'description_en': d['info_en'], 'description_de': d['info'],
            'expected_payload_len': resp_len(d['results']) if kind == 'did' else None,
            'n_fields': len(d['results']), 'vehicles': [],
            'relevance': 'battery' if ecu in BATTERY_ECUS else 'hv/charging/12v',
        }
    if d['name'] not in e['names']:
        e['names'].append(d['name'])
    if d['vehicle'] not in e['vehicles']:
        e['vehicles'].append(d['vehicle'])
    # conflicting layouts across generations: keep the shortest-known expected length as a hint only
    if kind == 'did':
        l = resp_len(d['results'])
        if l is not None and e['expected_payload_len'] not in (None, l):
            e['layout_differs_between_generations'] = True

rows = sorted(out.values(), key=lambda e: (e['ecu'] not in BATTERY_ECUS, e['ecu'], e['kind'], e['id']))
json.dump({'note': 'Read-only UDS requests for BMW EV/hybrid HV-battery related ECUs, merged across generations. '
                   'Send each to the ECU, save the raw response bytes (including negative responses).',
           'requests': rows}, open(H + '/data/scan_reads.json', 'w'), ensure_ascii=False, indent=1)
with open(H + '/data/scan_reads.csv', 'w', newline='') as f:
    w = csv.writer(f)
    w.writerow(['ecu', 'diag_addr_i3', 'kind', 'id', 'request', 'sweep', 'names', 'expected_payload_len',
                'layout_differs', 'vehicles', 'relevance', 'description_en'])
    for e in rows:
        w.writerow([e['ecu'], e['diag_addr_i3'], e['kind'], e['id'], e['request'],
                    '; '.join(f"{s['arg']} {s['start']}..{s['end']}" for s in e['sweep']), ' / '.join(e['names']),
                    e['expected_payload_len'] if e['expected_payload_len'] is not None else '',
                    'yes' if e.get('layout_differs_between_generations') else '', ' | '.join(e['vehicles']),
                    e['relevance'], e['description_en']])

from collections import Counter
print(len(rows), 'requests')
print(Counter((e['ecu'], e['kind']) for e in rows))
