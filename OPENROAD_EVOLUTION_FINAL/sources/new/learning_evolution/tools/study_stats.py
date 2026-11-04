#!/usr/bin/env python3
"""CSV-derived descriptive statistics and dependency-free SVG plots.

These describe simulated study labels, not real OpenROAD outcomes. There is
no statistically justified prediction of future tool improvement in this data.
"""
import argparse
from collections import Counter
import csv
import html
import importlib.util
import json
import math
from pathlib import Path
import statistics

FIELDS = {
    'simulated_wns_impact_pct': ('WNS improvement', '%'),
    'simulated_tns_impact_pct': ('TNS improvement', '%'),
    'simulated_runtime_delta_s': ('Runtime delta', 's'),
    'simulated_overall_score': ('Overall study score', 'score units'),
}
BLUE, ORANGE, INK, MUTED, GRID = '#326b96', '#b8753a', '#162939', '#526575', '#dce3e9'


def read_csv(path):
    with Path(path).open(newline='') as handle:
        return list(csv.DictReader(handle))


def write_csv(path, rows):
    if not rows:
        raise ValueError('Refusing to write an empty analytical table')
    with Path(path).open('w', newline='') as handle:
        writer = csv.DictWriter(handle, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)


def percentile(values, percentage):
    if not values or not 0 <= percentage <= 100:
        raise ValueError('Percentile needs data and a percentage in [0, 100]')
    ordered = sorted(values)
    position = (len(ordered) - 1) * percentage / 100
    low, high = math.floor(position), math.ceil(position)
    return ordered[low] + (ordered[high] - ordered[low]) * (position - low)


def describe(values, field, unit):
    if not values or not all(math.isfinite(value) for value in values):
        raise ValueError('Statistics need finite nonempty observations')
    width = .25 if unit == '%' else .1
    bins = Counter(math.floor(value / width) for value in values)
    # Deterministic tie-break: the lowest interval among equally common bins.
    modal = min(bins, key=lambda key: (-bins[key], key))
    return dict(metric=field, unit=unit, count=len(values),
                mean=statistics.mean(values), median=statistics.median(values),
                stddev=statistics.stdev(values) if len(values) > 1 else 0.,
                minimum=min(values), maximum=max(values),
                **{'p' + str(p): percentile(values, p) for p in [1, 5, 10, 25, 50, 75, 90, 95, 99]},
                modal_bin_low=modal * width, modal_bin_high=(modal + 1) * width,
                modal_bin_count=bins[modal], modal_bin_width=width)


class Svg:
    def __init__(self, title, subtitle, width=1050, height=520):
        self.width, self.height = width, height
        self.parts = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" viewBox="0 0 {width} {height}" role="img">',
                      f'<title>{html.escape(title)}</title>',
                      f'<rect width="{width}" height="{height}" fill="white"/>']
        self.text(32, 35, title, 20, INK)
        self.text(32, 60, subtitle, 12, MUTED)

    def text(self, x, y, value, size=12, fill=INK, anchor='start'):
        self.parts.append(f'<text x="{x}" y="{y}" fill="{fill}" font-size="{size}" font-family="Arial,sans-serif" text-anchor="{anchor}">{html.escape(str(value))}</text>')

    def line(self, x1, y1, x2, y2, color=GRID, width=1):
        self.parts.append(f'<line x1="{x1}" y1="{y1}" x2="{x2}" y2="{y2}" stroke="{color}" stroke-width="{width}"/>')

    def rect(self, x, y, width, height, fill):
        self.parts.append(f'<rect x="{x:.3f}" y="{y:.3f}" width="{max(0,width):.3f}" height="{max(0,height):.3f}" fill="{fill}"/>')

    def dot(self, x, y, radius=2, fill=BLUE, opacity=.4):
        self.parts.append(f'<circle cx="{x:.3f}" cy="{y:.3f}" r="{radius}" fill="{fill}" opacity="{opacity}"/>')

    def path(self, points, color):
        coordinates = ' '.join(f'{x:.3f},{y:.3f}' for x,y in points)
        self.parts.append(f'<polyline points="{coordinates}" fill="none" stroke="{color}" stroke-width="2.5"/>')

    def save(self, path):
        self.text(32, self.height - 15, 'Source: bundled CSV snapshot · no measured OpenROAD QoR', 11, MUTED)
        Path(path).write_text('\n'.join(self.parts + ['</svg>']) + '\n')


def axes(svg, xmax, ymax, xlabel, ylabel):
    left, top, width, height = 90, 100, 890, svg.height - 195
    for step in range(6):
        x = left + width * step / 5
        y = top + height - height * step / 5
        svg.line(left, y, left + width, y)
        svg.text(left - 12, y + 4, f'{ymax * step / 5:.3g}', anchor='end')
        svg.text(x, top + height + 22, f'{xmax * step / 5:.3g}', anchor='middle')
    svg.line(left, top, left, top + height, INK)
    svg.line(left, top + height, left + width, top + height, INK)
    svg.text(left, top - 13, ylabel, 12, MUTED)
    svg.text(left + width / 2, top + height + 48, xlabel, 12, MUTED, 'middle')
    return lambda x: left + width * x / xmax, lambda y: top + height - height * y / ymax


def bar_chart(path, title, subtitle, labels, values, xlabel):
    chart = Svg(title, subtitle, height=max(520, 220 + 31 * len(labels)))
    left, right = 360, 960
    maximum = max(values) or 1
    for index, (label, value) in enumerate(zip(labels, values)):
        y = 105 + index * 31
        chart.text(left - 12, y + 14, label, 12, anchor='end')
        chart.rect(left, y, (right - left) * value / maximum, 19, BLUE)
        chart.text(left + (right - left) * value / maximum + 8, y + 14, f'{value:.4g}')
    bottom = 115 + len(labels) * 31
    chart.line(left, bottom, right, bottom, INK)
    for index in range(5):
        x = left + (right - left) * index / 4
        chart.text(x, bottom + 20, f'{maximum * index / 4:.4g}', anchor='middle')
    chart.text((left + right) / 2, bottom + 43, xlabel, 12, MUTED, 'middle')
    chart.save(path)


def graphs(root, rows, applied):
    output = root / 'graphs'
    output.mkdir(exist_ok=True)
    wns = [float(row['simulated_wns_impact_pct']) for row in rows]
    tns = [float(row['simulated_tns_impact_pct']) for row in rows]
    chart = Svg('Distribution of simulated timing improvements', 'WNS (blue) and TNS (orange) · all 3,500 proposed policy variants')
    bins = [[0] * 20 for _ in range(2)]
    for destination, values in zip(bins, [wns, tns]):
        for value in values:
            destination[min(19, int(value / .25))] += 1
    xx, yy = axes(chart, 5, max(max(b) for b in bins) * 1.12,
                  'Simulated improvement (%) · bins of 0.25 percentage points', 'Candidate count')
    for group in range(20):
        for offset, (histogram, color) in enumerate(zip(bins, [BLUE, ORANGE])):
            x = xx(group * .25 + .015 + offset * .115)
            chart.rect(x, yy(histogram[group]), xx(.105) - xx(0), yy(0) - yy(histogram[group]), color)
    chart.text(770, 82, 'WNS', 12, BLUE)
    chart.text(850, 82, 'TNS', 12, ORANGE)
    chart.save(output / 'improvement_distribution.svg')
    chart = Svg('Percentiles of simulated timing improvements', 'Empirical quantiles with linear interpolation · all candidates; no selection filtering')
    xx, yy = axes(chart, 100, 5, 'Percentile (%)', 'Simulated improvement (%)')
    for values, color in [(wns, BLUE), (tns, ORANGE)]:
        chart.path([(xx(p), yy(percentile(values, p))) for p in range(101)], color)
    chart.text(770, 82, 'WNS', 12, BLUE)
    chart.text(850, 82, 'TNS', 12, ORANGE)
    chart.save(output / 'improvement_percentiles.svg')
    chart = Svg('WNS versus TNS study labels', 'One point per proposed variant · the label generator creates these clusters')
    xx, yy = axes(chart, 5, 5, 'Simulated WNS improvement (%)', 'Simulated TNS improvement (%)')
    for x, y in zip(wns, tns):
        chart.dot(xx(x), yy(y), 1.8, BLUE, .23)
    chart.save(output / 'wns_tns_scatter.svg')
    # Distinguish actual source-edit concentration from simulated QoR labels.
    counts = Counter()
    for row in applied:
        if row['target_path'].startswith('src/') and Path(row['target_path']).suffix in {'.cpp', '.cc', '.h', '.hh'}:
            counts[row['target_path']] += int(row['lines_added']) + int(row['lines_removed'])
    selected = counts.most_common(12)
    labels = [('/'.join(path.split('/')[1:2]) + '/' + Path(path).name) for path,_ in selected]
    bar_chart(output / 'source_change_concentration.svg', 'Where the actual source changes are concentrated',
              'Applied production-source changes · embedded definitions count at each source location',
              labels, [count for _,count in selected], 'Changed lines (added + removed)')
    top = sorted(rows, key=lambda row: float(row['simulated_overall_score']), reverse=True)[:10]
    bar_chart(output / 'highest_labeled_candidates.svg', 'Highest-scoring candidates in the study labels',
              'Ranking by simulated_overall_score · this is not an experimentally optimal code change',
              [row['change_hash'][:12] for row in top],
              [float(row['simulated_overall_score']) for row in top], 'Simulated score (arbitrary units)')
    fields = Counter(field for row in rows for field in row['changed_fields'].split(';'))
    bar_chart(output / 'changed_policy_fields.svg', 'Which policy fields the proposed variants edit',
              'Nonexclusive counts: one patch may edit multiple fields', list(fields), list(fields.values()), 'Candidate patches touching field (count)')
    return [str(path.relative_to(root)) for path in sorted(output.glob('*.svg'))]


def analyze(root, print_report=True):
    root = Path(root).resolve()
    rows = read_csv(root / 'data/candidates.csv')
    applied = read_csv(root / 'data/applied_changes.csv')
    output = root / 'statistics'
    output.mkdir(exist_ok=True)
    descriptions = []
    for field, (title, unit) in FIELDS.items():
        descriptions.append(describe([float(row[field]) for row in rows], field, unit))
    combined = [(float(row['simulated_wns_impact_pct']) + float(row['simulated_tns_impact_pct'])) / 2 for row in rows]
    descriptions.append(describe(combined, 'combined_timing_label_pct', '%'))
    write_csv(output / 'summary.csv', descriptions)
    (output / 'summary.json').write_text(json.dumps(descriptions, indent=2) + '\n')
    top = sorted(rows, key=lambda row: (-float(row['simulated_overall_score']), row['change_hash']))[:20]
    write_csv(output / 'highest_labeled_candidates.csv', top)
    concentration = Counter()
    for row in applied:
        concentration[row['target_path']] += int(row['lines_added']) + int(row['lines_removed'])
    write_csv(output / 'changes_by_file.csv', [dict(path=path, changed_lines=count)
              for path,count in concentration.most_common()])
    graph_paths = graphs(root, rows, applied)
    result = dict(provenance='descriptive statistics of simulated labels; not measured OpenROAD improvements',
                  candidate_count=len(rows), applied_hunks=len(applied),
                  summaries=descriptions, highest_labeled_candidate=top[0], graphs=graph_paths,
                  interpretation='The all-candidate mean describes this CSV only. Ranking fictional labels cannot identify an optimal real OpenROAD change.',
                  percentile_method='Linear interpolation at (n - 1) * p / 100',
                  mode_method='Most-populated fixed-width interval; lowest interval breaks ties. Continuous-valued exact modes are not emphasized.')
    (output / 'analysis.json').write_text(json.dumps(result, indent=2) + '\n')
    renderer = root / 'scripts/render_dashboard.py'
    if renderer.is_file():
        specification = importlib.util.spec_from_file_location('study_dashboard_renderer', renderer)
        module = importlib.util.module_from_spec(specification)
        specification.loader.exec_module(module)
        module.refresh(root, result, rows, read_csv(root / 'data/source_file_index.csv'))
    if print_report:
        print('CSV-DERIVED STUDY STATISTICS — simulated labels, not measured OpenROAD QoR')
        print(f'Candidates: {len(rows)}; applied source blocks: {len(applied)}')
        print(f'{"Metric":32} {"Mean":>9} {"Median":>9} {"Std dev":>9} {"P1":>9} {"P95":>9} {"P99":>9} {"Modal interval":>18}')
        for entry in descriptions:
            mode = f'[{entry["modal_bin_low"]:.2f}, {entry["modal_bin_high"]:.2f})'
            print(f'{entry["metric"]:32} {entry["mean"]:9.4f} {entry["median"]:9.4f} {entry["stddev"]:9.4f} {entry["p1"]:9.4f} {entry["p95"]:9.4f} {entry["p99"]:9.4f} {mode:>18}')
        print('Graphs:', root / 'graphs')
        print('No real-world expected improvement or optimal code change can be inferred from these simulated labels.')
    return result


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[1])
    analyze(parser.parse_args().root)
