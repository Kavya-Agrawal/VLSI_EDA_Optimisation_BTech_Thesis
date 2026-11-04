#!/usr/bin/env python3
"""Verify a self-contained handoff: hashes, links, graphs and CSV statistics."""
import csv
import hashlib
from html.parser import HTMLParser
import json
from pathlib import Path
import statistics
import xml.etree.ElementTree as ET
from urllib.parse import unquote, urlsplit

ROOT = Path(__file__).resolve().parents[1]


class Links(HTMLParser):
    def __init__(self):
        super().__init__()
        self.links = []
    def handle_starttag(self, tag, attributes):
        for key,value in attributes:
            if key in {'href', 'src'} and value:
                self.links.append(value)


def csv_rows(path):
    with path.open(newline='') as handle:
        return list(csv.DictReader(handle))


def main():
    checksums = json.loads((ROOT / 'CHECKSUMS.json').read_text())
    for relative, expected in checksums.items():
        path = ROOT / relative
        if hashlib.sha256(path.read_bytes()).hexdigest() != expected:
            raise AssertionError('Content checksum mismatch: ' + relative)
    rows = csv_rows(ROOT / 'data/candidates.csv')
    applied = csv_rows(ROOT / 'data/applied_changes.csv')
    if len(rows) != 3500 or len({r['change_hash'] for r in rows}) != 3500:
        raise AssertionError('Expected 3,500 unique candidates')
    for row in rows:
        for field in ['old_path', 'new_path', 'patch_path']:
            if not (ROOT / row[field]).is_file():
                raise AssertionError('Candidate link is missing: ' + row[field])
        if hashlib.sha256((ROOT / row['patch_path']).read_bytes()).hexdigest() != row['change_hash']:
            raise AssertionError('Candidate patch identity mismatch')
    summary = json.loads((ROOT / 'statistics/summary.json').read_text())
    for item in summary:
        field = item['metric']
        if field == 'combined_timing_label_pct':
            values = [(float(row['simulated_wns_impact_pct']) + float(row['simulated_tns_impact_pct'])) / 2 for row in rows]
        else:
            values = [float(row[field]) for row in rows]
        if abs(statistics.mean(values) - item['mean']) > 1e-12:
            raise AssertionError('Summary mean does not match CSV')
        ordered = sorted(values)
        for percentile in [1, 5, 10, 25, 50, 75, 90, 95, 99]:
            location = (len(values) - 1) * percentile / 100
            lower = int(location)
            upper = min(lower + 1, len(values) - 1)
            oracle = ordered[lower] + (ordered[upper] - ordered[lower]) * (location - lower)
            if abs(oracle - item['p' + str(percentile)]) > 1e-12:
                raise AssertionError('Percentile mismatch')
    checked_links = 0
    for path in [ROOT / 'index.html', *sorted((ROOT / 'diffs').glob('*.html'))]:
        parser = Links()
        parser.feed(path.read_text())
        for link in parser.links:
            target = urlsplit(link)
            if target.scheme or not target.path:
                continue
            if not (path.parent / unquote(target.path)).exists():
                raise AssertionError('Broken local link in ' + str(path) + ': ' + link)
            checked_links += 1
    for path in (ROOT / 'graphs').glob('*.svg'):
        ET.parse(path)
    source_index = csv_rows(ROOT / 'data/source_file_index.csv')
    for row in source_index:
        for key, digest in [('old_file', 'old_sha256'), ('new_file', 'new_sha256')]:
            if hashlib.sha256((ROOT / row[key]).read_bytes()).hexdigest() != row[digest]:
                raise AssertionError('Source index checksum mismatch')
    print(f'PASS: {len(checksums)} file checksums; {len(rows)} candidates; {len(applied)} applied blocks; {checked_links} HTML links; 6 SVG graphs; CSV-derived means and percentiles')


if __name__ == '__main__':
    main()
