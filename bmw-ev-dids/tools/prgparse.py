"""Minimal EDIABAS .prg/.grp table reader (format per uholeschak/ediabaslib EdiabasNet.cs)."""
import struct, sys, json

def _dec(b):
    return bytes(x ^ 0xF7 for x in b)

class Prg:
    def __init__(self, path):
        self.path = path
        self.data = open(path, 'rb').read()
        self.tables = {}
        self._read_tables()

    def _i32(self, off):
        return struct.unpack_from('<i', self.data, off)[0]

    def _read_tables(self):
        toff = self._i32(0x84)
        if toff < 0:
            return
        count = struct.unpack('<i', _dec(self.data[toff:toff + 4]))[0]
        pos = toff + 4
        for _ in range(count):
            hdr = _dec(self.data[pos:pos + 0x50])
            name = hdr[:0x40].split(b'\0')[0].decode('latin-1')
            coloff, cols, rows = struct.unpack_from('<I', hdr, 0x40)[0], *struct.unpack_from('<II', hdr, 0x48)
            self.tables[name.upper()] = (coloff, cols, rows)
            pos += 0x50

    def table(self, name):
        coloff, cols, rows = self.tables[name.upper()]
        p = coloff
        out = []
        for _ in range(rows + 1):
            row = []
            for _ in range(cols):
                e = p
                while self.data[e] ^ 0xF7:
                    e += 1
                row.append(_dec(self.data[p:e]).decode('cp1252', 'replace'))
                p = e + 1
            out.append(row)
        header = [h.upper() for h in out[0]]
        return [dict(zip(header, r)) for r in out[1:]]

    def version(self):
        off = self._i32(0x94)
        if off < 0:
            return {}
        b = _dec(self.data[off:off + 0x6C])
        return {
            'revision': '%d.%d' % (struct.unpack_from('<h', b, 6)[0], struct.unpack_from('<h', b, 4)[0]),
            'author': b[8:0x48].split(b'\0')[0].decode('cp1252', 'replace').strip(),
            'from': b[0x48:0x68].split(b'\0')[0].decode('cp1252', 'replace').strip(),
        }

    def header_comment(self, maxlines=40):
        """ECU description lines (ECU:, ORIGIN:, REVISION: ...) from the description block."""
        off = self._i32(0x90)
        if off < 0:
            return []
        n = struct.unpack_from('<i', self.data, off)[0]
        txt = _dec(self.data[off + 4:off + 4 + min(n, 20000)]).decode('cp1252', 'replace')
        lines = []
        for l in txt.split('\n'):
            if l.startswith('JOBNAME:'):
                break
            lines.append(l.strip())
        return lines[:maxlines]

if __name__ == '__main__':
    p = Prg(sys.argv[1])
    print(json.dumps(p.version()), p.header_comment()[:6])
    for t, (o, c, r) in p.tables.items():
        print(t, c, r)

def jobs(p):
    """[(jobname, comment)] from the description block."""
    off = p._i32(0x90)
    if off < 0:
        return []
    n = struct.unpack_from('<i', p.data, off)[0]
    txt = _dec(p.data[off + 4:off + 4 + n]).decode('cp1252', 'replace')
    out, cur = [], None
    for l in txt.split('\n'):
        l = l.strip()
        if l.startswith('JOBNAME:'):
            cur = [l[8:], '']
            out.append(cur)
        elif cur is not None and l.startswith('JOBCOMMENT:') and not cur[1]:
            cur[1] = l[11:]
    return out
