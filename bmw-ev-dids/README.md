# BMW EV / hybrid UDS DID catalogue

A list of the UDS data identifiers (DIDs), write identifiers and routines that BMW defines for its
electric and hybrid control units. It was extracted from the EDIABAS job files (SGBD `.prg`) that
Tool32, INPA and ISTA use.

| File | Contents |
|---|---|
| [`BMW_EV_DIDs.md`](BMW_EV_DIDs.md) | Coverage table plus one DID list per ECU, readable on GitHub |
| [`data/bmw_ev_dids.csv`](data/bmw_ev_dids.csv) | One row per DID/routine: vehicle, ECU, diag address, DID, service, job argument, English + German description |
| [`data/bmw_ev_did_fields.csv`](data/bmw_ev_did_fields.csv) | One row per response/argument field: byte offset, data type, unit, scaling (mul/div/add), bit masks |
| [`data/bmw_ev_dids.json`](data/bmw_ev_dids.json) | Everything above, nested |
| [`tools/`](tools) | The `.prg` parser and the scripts that produced the data |

## Coverage

| Vehicle family | Generation | ECUs | Source SGBDs |
|---|---|---|---|
| BMW i3 / i3s (I01) | Gen3 BEV, 2013-2022 | SME, EME, KLE (UCX2), LIM, IHX, EDME, REx REME + RDME | OVMS dumps of production SGBDs + 2012 SGBDs |
| BMW i8 (I12) | Gen3 PHEV, 2014-2020 | EME, REME | 2012 SGBDs |
| BMW 530Le (F18) | Gen2 PHEV | SME, EME | 2012 SGBDs |
| BMW X5 xDrive40e (F15) | Gen2 PHEV | SLE | 2012 SGBD |
| ActiveHybrid 3/5/7 (F30/F10/F01) | Hybrid Gen 2.0 | SME, EME | 2011-2012 SGBDs |
| ActiveHybrid 7 (F04) | Hybrid Gen 1.5 | SME, EME (8 SGBD variants merged) | 2008-2010 SGBDs |
| BMW ActiveE (E82 "BEV10") | Gen1 BEV | SME master, SMES1, SMES2, KLE | 2011-2012 SGBDs |

1,734 functions and about 13,600 response/argument fields in total.

**Not covered:** G-series and later EVs (iX3 G08, i4 G26, iX I20, i5, i7, iX1/iX2, Neue Klasse).
Their SGBDs have not been published anywhere public. Once you have their `.prg` files from a
current EDIABAS/ISTA install, the same tools will parse them (see below).

## How the data was produced

1. **SGBD files.** Non-i3 files come from the public `EDIABAS/Ecu` folder in the
   [bmw-advanced-tools](https://git.0x45.cz/em/bmw-advanced-tools) mirror, whose files date from
   2008-2012. For the i3, the [OVMS](https://github.com/openvehicles/Open-Vehicle-Monitoring-System-3/tree/master/vehicle/OVMS.V3/components/vehicle_bmwi3/dev)
   project publishes JSON dumps of newer, production-level SGBDs, which have up to 60% more DIDs
   (e.g. SME: 207 functions vs 127). Where both exist, the OVMS version is used, and DIDs found
   only in the 2012 file are kept and flagged `only_in_2012_sgbd`.
2. **Parsing.** `tools/prgparse.py` reads the `.prg` table section, following the format as
   implemented in [ediabaslib](https://github.com/uholeschak/ediabaslib) (`EdiabasNet.cs`): every
   byte is XOR `0xF7`, the table directory offset sits at file offset `0x84`, and cells are
   null-terminated strings. UDS SGBDs describe their generic `STATUS_LESEN` / `STEUERN` /
   `STEUERN_ROUTINE` jobs in the `SG_FUNKTIONEN` table, which points to `RES_0x....` (response
   layout) and `ARG_0x....` (request layout) tables.
3. **Byte offsets.** Computed the same way OVMS's generator does: fields are packed in table order
   by data type size, and `BITFIELD` fields take their size from their bit table. They match the
   OVMS i3 headers, e.g. `0xDFA0` min cell voltage at byte 6, `/10000` V. Offsets count from the
   first byte after the DID in the positive response (`62 DF A0 <byte 0> …`). Routine (`0x31`)
   tables mix start/stop/result parameters, so no offsets are given for them.
4. **Translation.** English descriptions come from OVMS's translations where the German text
   matches. The remaining ~3,500 strings were translated for this catalogue. The German original
   is always kept next to the English.

## Using a DID

```
request : 22 DD BF            (SME, i3: ISO-TP ext. address 0x07, tester 0xF1 -> CAN 0x6F1 / 0x607)
response: 62 DD BF 0F 6A 0F 7C
          STAT_UCELL_MIN_WERT = 0x0F6A / 1000 = 3.946 V
          STAT_UCELL_MAX_WERT = 0x0F7C / 1000 = 3.964 V
```

Service `2E` (write), `2F` (IO control) and `31` (routine) entries change ECU state: they open or
close contactors, change SoC limits, and reset NV data or cell capacities. They are listed for
reference. Several of them can disable the HV system.

## Regenerating

```sh
# 1. SGBD sources
git clone --filter=blob:none --sparse https://github.com/openvehicles/Open-Vehicle-Monitoring-System-3 ovms
(cd ovms && git sparse-checkout set vehicle/OVMS.V3/components/vehicle_bmwi3/dev)
#    …and put the .prg files in a folder, named ECU__<name>.prg (see GROUPS in build.py)

# 2. build + export
export OVMS_DEV=$PWD/ovms/vehicle/OVMS.V3/components/vehicle_bmwi3/dev PRG_PREFIX=$PWD/prg/ECU__ WORKDIR=$PWD/tools
python3 tools/build.py && python3 tools/export.py out/
```

To add a newer vehicle, add a row to `GROUPS` in `tools/build.py` pointing at its SGBDs.
`python3 tools/prgparse.py file.prg` lists the tables in any SGBD.

## Licence

The i3 data derived from OVMS's JSON dumps is GPL-3.0, as OVMS and ediabaslib are. The SGBD
descriptions themselves are BMW's. No `.prg` files are included in this repository.
