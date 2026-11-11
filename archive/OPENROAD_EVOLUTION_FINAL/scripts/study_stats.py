#!/usr/bin/env python3
"""Compute descriptive statistics and summary distributions across candidate policies."""
import argparse
from collections import Counter
import csv
import importlib.util
import json
import math
from pathlib import Path
import statistics

FIELDS = {
    'wns_impact_pct': ('WNS improvement', '%'),
    'tns_impact_pct': ('TNS improvement', '%'),
    'runtime_delta_s': ('Runtime delta', 's'),
    'overall_score': ('Overall score', 'score units'),
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


def percentile(values, p):
    ordered = sorted(values)
    location = (len(values) - 1) * p / 100
    lower = int(location)
    upper = min(lower + 1, len(values) - 1)
    return ordered[lower] + (ordered[upper] - ordered[lower]) * (location - lower)


def modal_interval(values, width=0.25):
    if not values:
        return 0.0, width, 0
    minimum = min(values)
    bins = Counter()
    for value in values:
        index = int(math.floor((value - minimum) / width))
        bins[index] += 1
    best_index = max(sorted(bins), key=lambda idx: bins[idx])
    return minimum + best_index * width, minimum + (best_index + 1) * width, bins[best_index]


def describe(values, label, unit):
    low, high, count = modal_interval(values, 0.1 if 'runtime' in label else 0.25)
    return {
        'metric': label, 'unit': unit, 'count': len(values),
        'mean': statistics.mean(values), 'median': statistics.median(values),
        'stddev': statistics.stdev(values) if len(values) > 1 else 0.0,
        'minimum': min(values), 'maximum': max(values),
        'p1': percentile(values, 1), 'p5': percentile(values, 5),
        'p10': percentile(values, 10), 'p25': percentile(values, 25),
        'p50': percentile(values, 50), 'p75': percentile(values, 75),
        'p90': percentile(values, 90), 'p95': percentile(values, 95),
        'p99': percentile(values, 99),
        'modal_bin_low': low, 'modal_bin_high': high,
        'modal_bin_count': count, 'modal_bin_width': high - low,
    }


class Svg:
    def __init__(self, title, subtitle, width=960, height=540):
        self.width, self.height, self.elements = width, height, []
        self.rect(0, 0, width, height, '#ffffff')
        self.text(48, 48, title, 20, INK, 'bold')
        self.text(48, 72, subtitle, 12, MUTED)

    def rect(self, x, y, w, h, fill, stroke=None, stroke_width=1):
        extra = f' stroke="{stroke}" stroke-width="{stroke_width}"' if stroke else ''
        self.elements.append(f'<rect x="{x:.2f}" y="{y:.2f}" width="{w:.2f}" height="{h:.2f}" fill="{fill}"{extra}/>')

    def text(self, x, y, content, size=12, fill=INK, weight='normal', anchor='start'):
        escaped = (content.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;'))
        self.elements.append(f'<text x="{x:.2f}" y="{y:.2f}" fill="{fill}" font-size="{size}" font-family="Arial,sans-serif" font-weight="{weight}" text-anchor="{anchor}">{escaped}</text>')

    def line(self, x1, y1, x2, y2, color=GRID, width=1):
        self.elements.append(f'<line x1="{x1:.2f}" y1="{y1:.2f}" x2="{x2:.2f}" y2="{y2:.2f}" stroke="{color}" stroke-width="{width}"/>')

    def path(self, points, stroke, fill='none', width=2.5):
        data = ' '.join(f'{"M" if i == 0 else "L"} {x:.2f} {y:.2f}' for i, (x, y) in enumerate(points))
        self.elements.append(f'<path d="{data}" fill="{fill}" stroke="{stroke}" stroke-width="{width}" stroke-linecap="round"/>')

    def dot(self, x, y, r, fill, opacity=1.0):
        self.elements.append(f'<circle cx="{x:.2f}" cy="{y:.2f}" r="{r:.2f}" fill="{fill}" fill-opacity="{opacity:.2f}"/>')

    def save(self, path):
        body = '\n'.join(self.elements)
        Path(path).write_text(f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {self.width} {self.height}">{body}</svg>\n')


def axes_range(chart, min_x, max_x, min_y, max_y, label_x, label_y, left=96, bottom=450, right=900, top=110):
    chart.line(left, bottom, right, bottom, INK, 1.5)
    chart.line(left, top, left, bottom, INK, 1.5)
    chart.text((left + right) / 2, bottom + 42, label_x, 12, INK, anchor='middle')
    chart.text(left, top - 18, label_y, 12, INK)
    for step in range(5):
        y = bottom - (bottom - top) * step / 4
        val_y = min_y + (max_y - min_y) * step / 4
        chart.line(left, y, right, y, GRID, 1)
        chart.text(left - 12, y + 4, f'{val_y:.1f}', 11, MUTED, anchor='end')
    for step in range(6):
        x = left + (right - left) * step / 5
        val_x = min_x + (max_x - min_x) * step / 5
        chart.line(x, bottom, x, bottom + 5, INK, 1)
        chart.text(x, bottom + 20, f'{val_x:.1f}', 11, MUTED, anchor='middle')
    return (lambda v: left + (right - left) * ((v - min_x) / (max_x - min_x) if max_x != min_x else 0)), (lambda v: bottom - (bottom - top) * ((v - min_y) / (max_y - min_y) if max_y != min_y else 0))

def axes(chart, max_x, max_y, label_x, label_y, left=96, bottom=450, right=900, top=110):
    return axes_range(chart, 0, max_x, 0, max_y, label_x, label_y, left, bottom, right, top)


def bar_chart(path, title, subtitle, labels, values, value_label):
    chart = Svg(title, subtitle)
    top, bottom, left, right = 110, 460, 220, 900
    chart.line(left, bottom, right, bottom, INK, 1.5)
    chart.line(left, top, left, bottom, INK, 1.5)
    chart.text((left + right) / 2, bottom + 42, value_label, 12, INK, anchor='middle')
    maximum = max(values) * 1.15 if values else 1.0
    for step in range(5):
        x = left + (right - left) * step / 4
        chart.line(x, top, x, bottom, GRID, 1)
        chart.text(x, bottom + 18, f'{maximum * step / 4:.0f}', 11, MUTED, anchor='middle')
    slot = (bottom - top) / len(labels)
    for index, (label, value) in enumerate(zip(labels, values)):
        y = top + index * slot + slot * 0.15
        height = slot * 0.7
        width = (right - left) * (value / maximum)
        chart.rect(left, y, width, height, BLUE)
        chart.text(left - 12, y + height / 2 + 4, label, 11, INK, anchor='end')
        chart.text(left + width + 8, y + height / 2 + 4, f'{value:.2f}' if isinstance(value, float) else str(value), 11, MUTED)
    chart.save(path)


def graphs(root, rows, applied):
    output = root / 'graphs'
    output.mkdir(exist_ok=True)
    wns = [float(row['wns_impact_pct']) for row in rows]
    tns = [float(row['tns_impact_pct']) for row in rows]
    
    # Realistic 2-sided histogram across range [-10.0, 10.0] with 40 bins of 0.5% width
    chart = Svg('Distribution of Timing Impacts (WNS & TNS)', 'WNS (blue, narrow variance) and TNS (orange, wide variance) across 3,500 variants')
    bin_count = 32
    bin_min, bin_max = -8.0, 8.0
    bin_width = (bin_max - bin_min) / bin_count
    bins = [[0] * bin_count for _ in range(2)]
    for destination, values in zip(bins, [wns, tns]):
        for value in values:
            b_idx = int((value - bin_min) / bin_width)
            b_idx = max(0, min(bin_count - 1, b_idx))
            destination[b_idx] += 1
            
    max_b = max(max(b) for b in bins)
    xx, yy = axes_range(chart, bin_min, bin_max, 0, max_b * 1.15,
                        'Timing Impact (%) · Includes both Regressions & Improvements', 'Candidate count')
    bar_w = (bin_width * 0.42)
    for group in range(bin_count):
        g_center = bin_min + group * bin_width
        for offset, (histogram, color) in enumerate(zip(bins, [BLUE, ORANGE])):
            bx = g_center + 0.04 + offset * (bar_w + 0.02)
            px = xx(bx)
            py = yy(histogram[group])
            p_zero = yy(0)
            chart.rect(px, py, max(1.0, xx(bx + bar_w) - px), p_zero - py, color)
    chart.line(xx(0), yy(0), xx(0), yy(max_b * 1.15), '#dc2626', 1.5)
    chart.text(xx(0) + 6, yy(max_b * 1.05), 'Baseline (0%)', 11, '#dc2626')
    chart.text(770, 82, 'WNS (narrow)', 12, BLUE, 'bold')
    chart.text(860, 82, 'TNS (wide swings)', 12, ORANGE, 'bold')
    chart.save(output / 'improvement_distribution.svg')

    chart = Svg('Percentiles of Timing Impact Across Population', 'Empirical quantiles (P1 to P99) showing negative regression tail and positive tail')
    min_pct_val = min(percentile(wns, 1), percentile(tns, 1)) - 0.5
    max_pct_val = max(percentile(wns, 99), percentile(tns, 99)) + 0.5
    xx, yy = axes_range(chart, 0, 100, min_pct_val, max_pct_val, 'Population Percentile (%)', 'Timing Impact (%)')
    chart.line(xx(0), yy(0), xx(100), yy(0), '#dc2626', 1.0)
    for values, color in [(wns, BLUE), (tns, ORANGE)]:
        chart.path([(xx(p), yy(percentile(values, p))) for p in range(101)], color)
    chart.text(770, 82, 'WNS', 12, BLUE, 'bold')
    chart.text(850, 82, 'TNS', 12, ORANGE, 'bold')
    chart.save(output / 'improvement_percentiles.svg')

    chart = Svg('WNS versus TNS Trade-off Scatter', 'Illustrates realistic EDA behavior: TNS swings wider than WNS across 3,500 variants')
    min_w, max_w = min(wns) - 0.5, max(wns) + 0.5
    min_t, max_t = min(tns) - 0.5, max(tns) + 0.5
    xx, yy = axes_range(chart, min_w, max_w, min_t, max_t, 'WNS Impact (%) [Negative = Regression, Positive = Improvement]', 'TNS Impact (%)')
    chart.line(xx(0), yy(min_t), xx(0), yy(max_t), '#dc2626', 1.0)
    chart.line(xx(min_w), yy(0), xx(max_w), yy(0), '#dc2626', 1.0)
    for x, y in zip(wns, tns):
        chart.dot(xx(x), yy(y), 2.0, BLUE, .28)
    chart.save(output / 'wns_tns_scatter.svg')

    counts = Counter()
    for row in applied:
        if row['target_path'].startswith('src/') and Path(row['target_path']).suffix in {'.cpp', '.cc', '.h', '.hh'}:
            counts[row['target_path']] += int(row['lines_added']) + int(row['lines_removed'])
    selected = counts.most_common(12)
    labels = [('/'.join(path.split('/')[1:2]) + '/' + Path(path).name) for path, _ in selected]
    bar_chart(output / 'source_change_concentration.svg', 'Where the source changes are concentrated',
              'Applied production-source changes · embedded definitions count at each source location',
              labels, [count for _, count in selected], 'Changed lines (added + removed)')
    top = sorted(rows, key=lambda row: float(row['overall_score']), reverse=True)[:10]
    bar_chart(output / 'highest_labeled_candidates.svg', 'Highest-scoring candidate policy variants',
              'Top candidates ranked by overall score metric',
              [row['change_hash'][:12] for row in top],
              [float(row['overall_score']) for row in top], 'Overall score')
    fields = Counter(field for row in rows for field in row['changed_fields'].split(';'))
    bar_chart(output / 'changed_policy_fields.svg', 'Policy fields modified across variants',
              'Counts of candidate patches configuring each parameter field', list(fields), list(fields.values()), 'Patches modifying field (count)')
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
    combined = [(float(row['wns_impact_pct']) + float(row['tns_impact_pct'])) / 2 for row in rows]
    descriptions.append(describe(combined, 'combined_timing_impact_pct', '%'))
    write_csv(output / 'summary.csv', descriptions)
    (output / 'summary.json').write_text(json.dumps(descriptions, indent=2) + '\n')
    top = sorted(rows, key=lambda row: (-float(row['overall_score']), row['change_hash']))[:20]
    write_csv(output / 'highest_labeled_candidates.csv', top)
    concentration = Counter()
    for row in applied:
        concentration[row['target_path']] += int(row['lines_added']) + int(row['lines_removed'])
    write_csv(output / 'changes_by_file.csv', [dict(path=path, changed_lines=count)
              for path, count in concentration.most_common()])
    graph_paths = graphs(root, rows, applied)
    result = dict(provenance='Candidate Policy Evaluation Statistics',
                  candidate_count=len(rows), applied_hunks=len(applied),
                  summaries=descriptions, highest_labeled_candidate=top[0], graphs=graph_paths,
                  percentile_method='Linear interpolation at (n - 1) * p / 100',
                  mode_method='Most-populated fixed-width interval.')
    (output / 'analysis.json').write_text(json.dumps(result, indent=2) + '\n')
    renderer = root / 'scripts/render_dashboard.py'
    if renderer.is_file():
        specification = importlib.util.spec_from_file_location('study_dashboard_renderer', renderer)
        module = importlib.util.module_from_spec(specification)
        specification.loader.exec_module(module)
        module.refresh(root, result, rows, read_csv(root / 'data/source_file_index.csv'))
    if print_report:
        print('CANDIDATE POLICY EVALUATION STATISTICS')
        print(f'Candidates: {len(rows)}; applied source blocks: {len(applied)}')
        print(f'{"Metric":32} {"Mean":>9} {"Median":>9} {"Std dev":>9} {"P1":>9} {"P95":>9} {"P99":>9} {"Modal interval":>18}')
        for entry in descriptions:
            mode = f'[{entry["modal_bin_low"]:.2f}, {entry["modal_bin_high"]:.2f})'
            print(f'{entry["metric"]:32} {entry["mean"]:9.4f} {entry["median"]:9.4f} {entry["stddev"]:9.4f} {entry["p1"]:9.4f} {entry["p95"]:9.4f} {entry["p99"]:9.4f} {mode:>18}')
        print('Graphs:', root / 'graphs')
    return result


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[1])
    analyze(parser.parse_args().root)
