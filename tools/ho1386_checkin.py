#!/usr/bin/env python3
"""Print check-in counter, gate, terminal and status for a Haneda international departure.

Data source: Tokyo Haneda Airport's public departures feed (the same JSON the
tokyo-haneda.com flight search uses). Default flight: Juneyao Air HO1386 (ICAO DKH1386)
to Shanghai Pudong.

Usage: ho1386_checkin.py [AIRLINE_ICAO] [FLIGHT_NUMBER]
"""
import json
import sys
import urllib.request

FEED = "https://tokyo-haneda.com/app_resource/flight/data/int/hdacfdep.json"

# Remark codes observed in the feed (備考コード). Code 10 has an empty English
# remark, which is how Haneda represents a flight whose check-in has not opened.
REMARK = {
    "10": "check-in not open yet",
    "11": "check-in open",
    "14": "now boarding",
    "15": "final call",
    "16": "gate closed",
    "17": "departed",
}


def fetch(url=FEED):
    req = urllib.request.Request(url, headers={"User-Agent": "Mozilla/5.0"})
    with urllib.request.urlopen(req, timeout=30) as r:
        return json.load(r)


def find(data, airline, number):
    for f in data["flight_info"]:
        for a in f["航空会社"]:
            if a["ＡＬコード"] == airline and a["便名"] == number:
                yield f
                break


def main():
    airline = sys.argv[1] if len(sys.argv) > 1 else "DKH"
    number = sys.argv[2] if len(sys.argv) > 2 else "1386"
    data = fetch()
    print(f"feed updated: {data['last_upd']} JST")
    hits = list(find(data, airline, number))
    if not hits:
        print(f"no {airline}{number} in feed")
        return 1
    for f in hits:
        codes = "/".join(a["ＡＬコード"] + a["便名"] for a in f["航空会社"])
        print(
            f"{codes} -> {f['行先地空港英名称']} ({f['行先地空港コード']})\n"
            f"  scheduled : {f['定刻']} JST\n"
            f"  estimated : {f['変更時刻'] or '-'}\n"
            f"  terminal  : {f['ターミナル区分']}\n"
            f"  check-in  : counter {f['チェックインカウンター番号'] or '-'}\n"
            f"  gate      : {f['ゲート番号コード'] or '-'}\n"
            f"  status    : {f['備考英名称'] or '-'} "
            f"(code {f['備考コード'] or '-'}: {REMARK.get(f['備考コード'], 'unknown')})"
        )
    return 0


if __name__ == "__main__":
    sys.exit(main())
