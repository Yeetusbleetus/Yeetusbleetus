"""Apply translations and export DID dataset as CSV / JSON / Markdown."""
import json, csv, glob, os, sys
from collections import OrderedDict, Counter

S = os.environ.get('WORKDIR', os.path.dirname(os.path.abspath(__file__)))
OUT = sys.argv[1] if len(sys.argv) > 1 else S + '/out'
os.makedirs(OUT, exist_ok=True)

raw = json.load(open(S + '/dids_raw.json'))
tr = json.load(open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'translations_de_en.json')))

def en(de, en_):
    return en_ or tr.get(de, '') if de else en_

SERV = {'22': 'read', '2E': 'write', '31': 'routine', '2F': 'io-control', '22;2E': 'read/write', '2E;22': 'read/write',
        '22;2C': 'read (dyn. DID)', '22;2F': 'read/io-control'}

missing = 0
for d in raw['dids']:
    d['info_en'] = en(d['info'], d['info_en'])
    missing += bool(d['info'] and not d['info_en'])
    for r in d['results'] + d['args']:
        r['info_en'] = en(r['info'], r['info_en'])
        missing += bool(r['info'] and not r['info_en'])
        for b in r.get('bits', []):
            b['info_en'] = en(b['info'], b['info_en'])
print('missing translations:', missing, file=sys.stderr)

dids = raw['dids']
json.dump(raw, open(OUT + '/bmw_ev_dids.json', 'w'), ensure_ascii=False, indent=1)

cols = ['vehicle', 'generation', 'ecu', 'role', 'diag_addr', 'did', 'service', 'service_type', 'job_arg', 'description_en',
        'description_de', 'n_result_fields', 'n_arg_fields', 'single_result_type', 'single_result_unit', 'sources',
        'only_in_2012_sgbd']
with open(OUT + '/bmw_ev_dids.csv', 'w', newline='') as f:
    w = csv.writer(f)
    w.writerow(cols)
    for d in dids:
        one = d['results'][0] if len(d['results']) == 1 else {}
        w.writerow([d['vehicle'], d['generation'], d['ecu'], d['role'], d['addr'], d['did'], d['service'],
                    SERV.get(d['service'], d['service']), d['name'], d['info_en'], d['info'], len(d['results']),
                    len(d['args']), one.get('type', ''), one.get('unit', ''), ' | '.join(d['sources']),
                    'yes' if d['only_old'] else ''])

fcols = ['vehicle', 'ecu', 'did', 'service', 'job_arg', 'direction', 'routine_phase', 'idx', 'byte_offset', 'name',
         'type', 'unit', 'mul', 'div', 'add', 'mask', 'min', 'max', 'value_table', 'description_en', 'description_de']
with open(OUT + '/bmw_ev_did_fields.csv', 'w', newline='') as f:
    w = csv.writer(f)
    w.writerow(fcols)
    for d in dids:
        for kind in ('results', 'args'):
            for r in d[kind]:
                w.writerow([d['vehicle'], d['ecu'], d['did'], d['service'], d['name'], kind[:-1], r['routine_phase'],
                            r['idx'], r['offset'], r['name'], r['type'], r['unit'], r['mul'], r['div'], r['add'],
                            r['mask'], r['min'], r['max'], r['table'], r['info_en'], r['info']])
                for b in r.get('bits', []):
                    w.writerow([d['vehicle'], d['ecu'], d['did'], d['service'], d['name'], kind[:-1] + '_bit', '',
                                r['idx'], r['offset'], b['name'], 'bit', '', '', '', '', b['mask'], '', '', r['name'],
                                b['info_en'], b['info']])

# compact JSON for the web page
def cf(r):
    o = [r['offset'], r['name'], r['type'], r['unit'],
         '' if (r['mul'] in ('1.0', '1', '') and r['div'] in ('1.0', '1', '') and r['add'] in ('0.0', '0', ''))
         else f"*{r['mul']}/{r['div']}+{r['add']}", r['info_en'] or r['info'], r['routine_phase'], r['mask']]
    if r.get('bits'):
        o.append([[b['name'], b['mask'], b['info_en'] or b['info']] for b in r['bits']])
    return o
groups = OrderedDict()
for d in dids:
    groups.setdefault(d['group'], {k: d[k] for k in ('vehicle', 'generation', 'ecu', 'role', 'addr')})
web = {'groups': groups, 'sources': raw['meta'],
       'rows': [[d['group'], d['did'], d['service'], d['name'], d['info_en'] or d['info'], d['info'],
                 [cf(r) for r in d['results']], [cf(r) for r in d['args']], int(d['only_old'])] for d in dids]}
json.dump(web, open(OUT + '/web.json', 'w'), ensure_ascii=False, separators=(',', ':'))

# markdown index
md = ['# BMW EV / hybrid UDS DID catalogue', '',
      'Generated from EDIABAS SGBD `SG_FUNKTIONEN` tables. See `tools/` for the parser.', '',
      '| Vehicle | Generation | ECU | Role | Diag addr | Functions | Read | Write | Routine | Sources |',
      '|---|---|---|---|---|---:|---:|---:|---:|---|']
for gid, g in groups.items():
    ds = [d for d in dids if d['group'] == gid]
    c = Counter(SERV.get(d['service'], d['service']).split(' ')[0] for d in ds)
    srcs = sorted({s for d in ds for s in d['sources']})
    md.append(f"| {g['vehicle']} | {g['generation']} | {g['ecu']} | {g['role']} | {g['addr']} | {len(ds)} | "
              f"{c['read'] + c['read/write']} | {c['write'] + c['read/write']} | {c['routine']} | {'<br>'.join(srcs)} |")
for gid, g in groups.items():
    md += ['', f"## {g['vehicle']} — {g['ecu']} ({g['role']})", '', '| DID | Svc | Job argument | Description | Fields |',
           '|---|---|---|---|---:|']
    for d in dids:
        if d['group'] != gid:
            continue
        desc = (d['info_en'] or d['info']).replace('|', '/').replace('\n', ' ')
        if d['only_old']:
            desc += ' *(2012 SGBD only)*'
        md.append(f"| `{d['did']}` | {d['service']} | `{d['name']}` | {desc} | {len(d['results']) + len(d['args'])} |")
open(OUT + '/BMW_EV_DIDs.md', 'w').write('\n'.join(md) + '\n')
print(len(dids), 'functions exported to', OUT, file=sys.stderr)
