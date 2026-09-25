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
| [`data/scan_reads.csv`](data/scan_reads.csv) / [`.json`](data/scan_reads.json) | Read-only scan list: every battery-related read request across all generations (see below) |
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

## Read-only scan list

`data/scan_reads.json` (and `.csv`) lists every read request relevant to the HV battery, merged across
generations per ECU type, so one script can send them all to any car and keep the raw bytes:

| kind | Request | What it is |
|---|---|---|
| `did` | `22 XX XX` | Every 0x22 DID of the battery ECUs (SME, SMES1/2). From EME, KLE, LIM, SLE, IHX, EDME, REME, RDME only DIDs about the HV battery, charging, isolation, contactors, DC/DC or the 12V battery. Gen1.5 hybrids keep a lot of battery history in the EME. |
| `routine_read` | `31 01 XX XX <index>`, then `followup` `31 03 XX XX` | Routines that only read data, indexed by cell, module, CSC, history record or histogram number, e.g. `ZELLSPANNUNG_LESEN` (0xAD6E, one cell voltage per call; i3 cells are 1..96). Start with the index, then fetch the value with request-results. `sweep` gives the argument and a range to try. |
| `routine_results` | `31 03 XX XX` | Test/actuation routines (isolation test, capacity test, heating, balancing). Only *request results* is listed: it returns the last stored result and does not start the routine. Never send `31 01` for these. |

Numbers: 617 DIDs (23 of them community-documented for Gen4 PHEV and Gen5 iX/i4, `source: community`), 18 read routines (swept), 9 results-only routines. Each entry carries the ECU,
the i3 diagnostic address, the vehicles whose SGBD defines it, and `expected_payload_len` when the
layout is fixed. `layout_differs` marks DIDs whose layout changes between generations, so decode
them with the table for the matching vehicle in `bmw_ev_dids.json`.

Recommended scan procedure:

1. Start in the default session. If a request returns `7F 22 7F` (not supported in this session) or `7F 22 33`,
   switch to the extended session (`10 03`) and retry. `7F 22 31` just means the DID doesn't exist on this car.
2. For every entry, send the request to the ECU's address and store `{ecu, request, response hex, timestamp}`.
   Negative responses are data too: `7F 22 31` = DID not supported on this car.
3. For `routine_read`, loop the index over `sweep.start..sweep.end`, append it as `sweep.bytes` bytes, and stop after a few
   consecutive `7F 31 31` (request out of range).
4. Send `3E 00` (tester present) every ~2 s during long sweeps.

Unsupported entries simply return `7F`, so one list works for every generation.

### Generations without public SGBDs

- **Community DIDs:** `data/community_dids.json` lists read requests that open-source projects use on Gen4 PHEV and
  Gen5 (iX/i4/i5/i7) batteries, with the byte layouts they decode. The source is mainly
  [Battery-Emulator](https://github.com/dalathegreat/Battery-Emulator). Highlights: Gen4 PHEV `22 DF A5` returns all 96
  cell voltages; Gen5 has `22 E5 54` (all cell voltages), `22 E5 9A` (cell SoC), `22 E5 CA` (cell temperatures),
  `22 E5 45` (SoH), `22 E5 C7` (kWh capacity), `22 A8 60` (isolation). The battery ECU is at address `0x07` on every
  generation. Gen4 PHEVs answer many of the same DIDs as the i3 (`0xDFA0`, `0xDD6A`, `0xDDC0`, …) with the same layout.
- **Discovery mode:** the `discovery` block in `scan_reads.json` describes a read-only brute-force: find ECU addresses,
  sweep every `22 XXXX` DID on the battery ECU (priority ranges first, full range ~15-20 min), optionally sweep routine
  IDs using only `31 03` (request results, never starts anything; existing routines answer `7F 31 24`), and read DTCs.
  It also lists how to interpret each negative response code.

## Regenerating

```sh
# 1. SGBD sources
git clone --filter=blob:none --sparse https://github.com/openvehicles/Open-Vehicle-Monitoring-System-3 ovms
(cd ovms && git sparse-checkout set vehicle/OVMS.V3/components/vehicle_bmwi3/dev)
#    …and put the .prg files in a folder, named ECU__<name>.prg (see GROUPS in build.py)

# 2. build + export
export OVMS_DEV=$PWD/ovms/vehicle/OVMS.V3/components/vehicle_bmwi3/dev PRG_PREFIX=$PWD/prg/ECU__ WORKDIR=$PWD/tools
python3 tools/build.py && python3 tools/export.py out/
python3 tools/scanlist.py   # rebuild data/scan_reads.* from data/bmw_ev_dids.json
```

To add a newer vehicle, add a row to `GROUPS` in `tools/build.py` pointing at its SGBDs.
`python3 tools/prgparse.py file.prg` lists the tables in any SGBD.

## Licence

The i3 data derived from OVMS's JSON dumps is GPL-3.0, as OVMS and ediabaslib are. The SGBD
descriptions themselves are BMW's. No `.prg` files are included in this repository.
