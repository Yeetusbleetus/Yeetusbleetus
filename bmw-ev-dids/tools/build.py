"""Build a merged DID dataset for BMW EV/hybrid ECUs from EDIABAS SGBDs."""
import json, os, re, csv, glob
from prgparse import Prg

S = os.environ.get('WORKDIR', os.path.dirname(os.path.abspath(__file__)))
# OVMS_DEV: OVMS vehicle_bmwi3/dev folder (JSON SGBD dumps); PRG_DIR: folder holding the EDIABAS Ecu/*.prg files
OVMS = os.environ.get('OVMS_DEV', S + '/ovms/vehicle/OVMS.V3/components/vehicle_bmwi3/dev') + '/'
PRG = os.environ.get('PRG_PREFIX', S + '/prg/ECU__')

# group -> (vehicle, generation, ecu, role, diag address, [sources newest first])
GROUPS = [
    ('i3_sme', 'BMW i3 / i3s (I01)', 'Gen3 BEV (2013-2022)', 'SME', 'HV battery management', '0x07',
     [('ovms', 'sme_i1'), ('prg', 'sme_i1')]),
    ('i3_eme', 'BMW i3 / i3s (I01)', 'Gen3 BEV (2013-2022)', 'EME', 'Drive inverter + DC/DC', '0x1A',
     [('ovms', 'eme_i01'), ('prg', 'eme_i01')]),
    ('i3_eme_alt', 'BMW i3 (I01)', 'Gen3 BEV (2013-2022)', 'EME', 'Drive electronics (alternate SGBD EME_I1)', '0x1A',
     [('prg', 'EME_I1')]),
    ('i3_kle', 'BMW i3 / i3s (I01)', 'Gen3 BEV (2013-2022)', 'KLE', 'On-board charger (UCX2)', '0x15',
     [('ovms', 'ucx2_i01')]),
    ('i3_lim', 'BMW i3 / i3s (I01)', 'Gen3 BEV (2013-2022)', 'LIM', 'Charge interface module', '0x14',
     [('ovms', 'lim_i1'), ('prg', 'lim_i1')]),
    ('i3_ihx', 'BMW i3 / i3s (I01)', 'Gen3 BEV (2013-2022)', 'IHX', 'Heating/AC, heat pump, HV heater', '0x78',
     [('ovms', 'ihx_i1'), ('prg', 'ihx_i1')]),
    ('i3_edme', 'BMW i3 / i3s (I01)', 'Gen3 BEV (2013-2022)', 'EDME', 'Vehicle control unit / 12V energy mgmt', '0x12',
     [('ovms', 'edmei1'), ('prg', 'edmei1')]),
    ('i3_reme', 'BMW i3 REx (I01)', 'Gen3 BEV (2013-2022)', 'REME', 'Range-extender generator electronics', '',
     [('prg', 'reme_i1')]),
    ('i3_rdme', 'BMW i3 REx (I01)', 'Gen3 BEV (2013-2022)', 'RDME', 'Range-extender engine DME', '',
     [('prg', 'rdme_i1')]),
    ('i8_eme', 'BMW i8 (I12)', 'Gen3 PHEV (2014-2020)', 'EME', 'Front e-machine electronics', '',
     [('prg', 'eme_i12')]),
    ('i8_reme', 'BMW i8 (I12)', 'Gen3 PHEV (2014-2020)', 'REME', 'High-voltage starter-generator electronics', '',
     [('prg', 'reme_i12')]),
    ('f18_sme', 'BMW 530Le (F18)', 'Gen2 PHEV (2014-2017, China)', 'SME', 'HV battery management', '',
     [('prg', 'sme_f18')]),
    ('f18_eme', 'BMW 530Le (F18)', 'Gen2 PHEV (2014-2017, China)', 'EME', 'E-machine electronics', '',
     [('prg', 'eme_f18')]),
    ('f15_sle', 'BMW X5 xDrive40e (F15)', 'Gen2 PHEV (2015-2018)', 'SLE', 'Charging electronics incl. LIM', '',
     [('prg', 'sle_f15')]),
    ('gen20_sme', 'ActiveHybrid 3/5/7 (F30/F10/F01)', 'Hybrid Gen 2.0 (2012-2016)', 'SME', 'HV battery management', '',
     [('prg', 'sme_10')]),
    ('gen20_eme', 'ActiveHybrid 3/5/7 (F30/F10/F01)', 'Hybrid Gen 2.0 (2012-2016)', 'EME', 'E-machine electronics', '',
     [('prg', 'eme_10')]),
    ('gen15_sme', 'ActiveHybrid 7 (F04)', 'Hybrid Gen 1.5 (2009-2012)', 'SME', 'HV battery management', '',
     [('prg', 'sme_04'), ('prg', 'SME_04_029')]),
    ('gen15_eme', 'ActiveHybrid 7 (F04)', 'Hybrid Gen 1.5 (2009-2012)', 'EME', 'E-machine electronics', '',
     [('prg', 'eme_04'), ('prg', 'EME_04_490'), ('prg', 'EME_04_I410'), ('prg', 'eme_04_alt'),
      ('prg', 'EME_04_nur_I300'), ('prg', 'eme_04_I260')]),
    ('e82_sme', 'BMW ActiveE (E82, "BEV10")', 'Gen1 BEV (2011-2013)', 'SME', 'HV battery management (master)', '',
     [('prg', 'SME_82')]),
    ('e82_smes1', 'BMW ActiveE (E82, "BEV10")', 'Gen1 BEV (2011-2013)', 'SMES1', 'HV battery management slave 1', '',
     [('prg', 'SMES1_82')]),
    ('e82_smes2', 'BMW ActiveE (E82, "BEV10")', 'Gen1 BEV (2011-2013)', 'SMES2', 'HV battery management slave 2', '',
     [('prg', 'SMES2_82')]),
    ('e82_kle', 'BMW ActiveE (E82, "BEV10")', 'Gen1 BEV (2011-2013)', 'KLE', 'On-board charger', '',
     [('prg', 'KLE_82E')]),
]

SIZES = {'signed char': 1, 'unsigned char': 1, 'char': 1, 'signed int': 2, 'unsigned int': 2, 'int': 2,
         'long': 4, 'signed long': 4, 'unsigned long': 4, 'float': 4, 'real': 4, 'motorola float': 4,
         'intel float': 4, 'double': 8, 'motorola double': 8, 'intel double': 8}
SERVICES = {'22': 'read (0x22)', '2E': 'write (0x2E)', '2F': 'io-control (0x2F)', '31': 'routine (0x31)',
            '22;2E': 'read/write', '2E;22': 'read/write'}


class Src:
    def __init__(self, kind, name):
        self.kind, self.name = kind, name
        if kind == 'ovms':
            d = json.load(open(OVMS + name + '.json'))
            self.t = {k.upper(): v for k, v in d['tables'].items()}
            self.label = f'{name}.prg (OVMS dump, GPL-3.0)'
            self.rev = ''
        else:
            p = Prg(PRG + name + '.prg')
            self.t = {k: p.table(k) for k in p.tables}
            v = p.version()
            self.label = f'{name}.prg rev {v["revision"]} ({v["from"][-4:]})'
            self.rev = v['revision']

    def table(self, n):
        return self.t.get((n or '').upper())


def val(x):
    return '' if x in (None, '-') else str(x).strip()


def layout(src, fields, kind):
    """Assign byte offsets per OVMS rules; returns list of field dicts."""
    out, off = [], 0
    for i, f in enumerate(fields):
        dt = val(f.get('DATENTYP'))
        rn = val(f.get('RESULTNAME')) or val(f.get('ARG')) or val(f.get('NAME'))
        size, bits = None, None
        if kind == 'res' and dt.upper() == 'BITFIELD':
            bt = src.table(val(f.get('NAME')) or rn)
            bits = [{'name': val(b.get('RESULTNAME')), 'mask': val(b.get('MASKE')), 'info': val(b.get('INFO')),
                     'info_en': val(b.get('INFO_EN'))} for b in (bt or [])]
            size = SIZES.get(val(bt[0].get('DATENTYP')), 1) if bt else None
        elif dt in SIZES:
            size = SIZES[dt]
        else:
            m = re.match(r'(?:data|string)\[(\d+)\]', dt)
            size = int(m.group(1)) if m else None
        rec = {
            'idx': i, 'offset': off if off is not None else '', 'name': rn, 'type': dt,
            'unit': val(f.get('EINHEIT')), 'mul': val(f.get('MUL')), 'div': val(f.get('DIV')), 'add': val(f.get('ADD')),
            'mask': val(f.get('MASKE')), 'table': val(f.get('NAME')), 'info': val(f.get('INFO')),
            'info_en': val(f.get('INFO_EN')), 'min': val(f.get('MIN')), 'max': val(f.get('MAX')),
            'routine_phase': ''.join(p for p, c in (('start ', 'STR'), ('stop ', 'STPR'), ('results ', 'RRR'))
                                     if val(f.get(c)) == '+').strip(),
        }
        if bits:
            rec['bits'] = bits
        out.append(rec)
        # routine arg/result lists restart per phase; don't compute cumulative offsets across phases
        if off is not None:
            off = None if size is None else off + size
    if kind == 'res' and any(r['routine_phase'] for r in out):
        for r in out:
            r['offset'] = ''
    return out


def build():
    dids, meta = [], []
    for gid, veh, gen, ecu, role, addr, sources in GROUPS:
        seen = {}
        for kind, name in sources:
            src = Src(kind, name)
            meta.append({'group': gid, 'vehicle': veh, 'generation': gen, 'ecu': ecu, 'source': src.label})
            for f in src.table('SG_FUNKTIONEN') or []:
                key = (val(f.get('ID')).upper(), val(f.get('SERVICE')).upper(), val(f.get('ARG')).upper())
                if key in seen:
                    seen[key]['sources'].append(src.label)
                    continue
                rt, at = val(f.get('RES_TABELLE')), val(f.get('ARG_TABELLE'))
                if rt:
                    res = layout(src, src.table(rt) or [], 'res')
                elif val(f.get('DATENTYP')):
                    res = layout(src, [f], 'res')
                else:
                    res = []
                args = layout(src, src.table(at) or [], 'arg') if at else []
                d = {
                    'group': gid, 'vehicle': veh, 'generation': gen, 'ecu': ecu, 'role': role, 'addr': addr,
                    'did': '0x' + val(f.get('ID'))[2:].upper(), 'service': val(f.get('SERVICE')).upper(),
                    'name': val(f.get('ARG')), 'label': val(f.get('LABEL')),
                    'info': val(f.get('INFO')), 'info_en': val(f.get('INFO_EN')),
                    'results': res, 'args': args, 'sources': [src.label],
                    'only_old': kind == 'prg' and sources[0][0] == 'ovms',
                }
                seen[key] = d
                dids.append(d)
    return dids, meta


if __name__ == '__main__':
    dids, meta = build()
    json.dump({'meta': meta, 'dids': dids}, open(S + '/dids_raw.json', 'w'), ensure_ascii=False)
    nf = sum(len(d['results']) + len(d['args']) for d in dids)
    print(len(dids), 'functions', nf, 'fields')
    from collections import Counter
    print(Counter(d['group'] for d in dids))
    print(Counter(d['service'] for d in dids))
    print(Counter(r['type'] for d in dids for r in d['results'] if r['type'] not in SIZES and r['type'] != 'BITFIELD'
                  and not re.match(r'(data|string)\[', r['type'])).most_common(20))
