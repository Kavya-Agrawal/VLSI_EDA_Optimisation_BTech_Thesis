#!/usr/bin/env python3
"""Report statistics computed from the simulated label CSV, without fixed metrics."""
import csv
from pathlib import Path
from study_stats import FIELDS, describe
HOME = Path(__file__).resolve().parents[1]


def main():
    with (HOME / 'dataset/changes.csv').open() as handle:
        rows = list(csv.DictReader(handle))
    summaries = [describe([float(row[field]) for row in rows], field, unit)
                 for field, (title,unit) in FIELDS.items()]
    lines = ['# CSV-derived OpenROAD evolution study summary', '',
             'Provenance: simulated labels, not measured OpenROAD QoR. These averages do not predict real improvement.', '',
             f'Candidate variants: {len(rows)}. All candidates are included; no high-score or acceptance filtering.', '',
             '| Label | Mean | Median | P1 | P95 | P99 |',
             '| --- | ---: | ---: | ---: | ---: | ---: |']
    for entry in summaries:
        values = ' | '.join(f'{entry[key]:.4f}' for key in ['mean','median','p1','p95','p99'])
        lines.append(f'| {entry["metric"]} ({entry["unit"]}) | {values} |')
    lines += ['', 'Percentiles: linear interpolation. Mode and complete statistics are in OPENROAD_EVOLUTION_FINAL/statistics/.',
              'Open OPENROAD_EVOLUTION_FINAL/index.html for source diffs, candidate code, six graphs and the full CSV.',
              'Algorithms are embedded directly in the changed OpenROAD translation units; full OpenROAD compilation remains unverified.', '']
    report = '\n'.join(lines)
    (HOME / 'REPORT.md').write_text(report)
    print(report)


if __name__ == '__main__':
    main()
