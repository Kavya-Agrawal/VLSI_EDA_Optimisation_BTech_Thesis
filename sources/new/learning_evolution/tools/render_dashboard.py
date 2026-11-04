"""Render clean, academic study dashboard, graphs page, and source code viewers."""
import csv
import hashlib
import html
import json
from pathlib import Path

FINAL = Path(__file__).resolve().parents[1]

ACADEMIC_CSS = """
body {
    font-family: "Latin Modern Roman", "Times New Roman", Times, Georgia, "DejaVu Serif", serif;
    color: #111;
    background: #fff;
    line-height: 1.55;
    margin: 40px auto;
    max-width: 1060px;
    padding: 0 24px;
}
h1 {
    font-size: 25px;
    font-weight: bold;
    border-bottom: 2px solid #222;
    padding-bottom: 8px;
    margin: 12px 0 16px 0;
}
h2 {
    font-size: 19px;
    font-weight: bold;
    border-bottom: 1px solid #888;
    padding-bottom: 4px;
    margin-top: 36px;
    margin-bottom: 14px;
}
h3 {
    font-size: 16px;
    font-weight: bold;
    margin-top: 20px;
    margin-bottom: 8px;
}
p {
    margin: 10px 0;
    line-height: 1.55;
}
a {
    color: #003399;
    text-decoration: underline;
}
a:visited {
    color: #4a154b;
}
a:hover {
    color: #b00;
}
.academic-nav {
    margin: 18px 0;
    padding: 8px 0;
    border-top: 1px solid #ccc;
    border-bottom: 1px solid #ccc;
    font-family: monospace, sans-serif;
    font-size: 13.5px;
}
.academic-nav a {
    margin-right: 18px;
    text-decoration: none;
    font-weight: bold;
}
.academic-nav a:hover {
    text-decoration: underline;
}
.summary-grid {
    display: table;
    width: 100%;
    margin: 16px 0;
    border: 1px solid #999;
    border-collapse: collapse;
}
.summary-grid td {
    border: 1px solid #bbb;
    padding: 10px 14px;
    vertical-align: top;
    width: 25%;
    background: #fafafa;
}
.summary-grid strong {
    display: block;
    font-size: 22px;
    font-family: monospace, sans-serif;
    margin-top: 4px;
}
table.academic-table {
    width: 100%;
    border-collapse: collapse;
    margin: 16px 0;
    font-size: 13px;
    border: 1px solid #888;
}
table.academic-table th, table.academic-table td {
    border: 1px solid #bbb;
    padding: 7px 10px;
    text-align: left;
    vertical-align: top;
}
table.academic-table th {
    background: #ebebeb;
    font-weight: bold;
}
table.academic-table tr:nth-child(even) {
    background: #fbfbfb;
}
code {
    font-family: Menlo, Monaco, Consolas, "Courier New", monospace;
    font-size: 12.5px;
    background: #f3f3f3;
    padding: 1px 4px;
    border: 1px solid #e0e0e0;
}
pre {
    background: #f8f8f8;
    border: 1px solid #ccc;
    padding: 14px;
    overflow-x: auto;
    font-family: Menlo, Monaco, Consolas, "Courier New", monospace;
    font-size: 12.5px;
    line-height: 1.45;
}
.scroll {
    max-height: 540px;
    overflow-y: auto;
    border: 1px solid #bbb;
}
.tools {
    margin: 12px 0;
    display: flex;
    gap: 12px;
    align-items: center;
    font-family: monospace, sans-serif;
    font-size: 13px;
    flex-wrap: wrap;
}
.tools input, .tools select, .tools button {
    font: inherit;
    padding: 6px 10px;
    border: 1px solid #999;
    background: #fff;
    border-radius: 2px;
}
.muted {
    color: #555;
    font-size: 13px;
}
figure.academic-fig {
    margin: 24px 0 32px 0;
    padding: 14px;
    border: 1px solid #ccc;
    background: #fafafa;
}
figure.academic-fig img {
    max-width: 100%;
    height: auto;
    display: block;
    margin: 0 auto;
    background: #fff;
    border: 1px solid #e0e0e0;
}
figcaption.academic-cap {
    font-size: 13.5px;
    color: #222;
    margin-top: 10px;
    line-height: 1.5;
    border-top: 1px solid #ddd;
    padding-top: 8px;
}
.code-view {
    font-family: Menlo, Monaco, Consolas, monospace;
    font-size: 12px;
    line-height: 1.4;
    white-space: pre;
    overflow-x: auto;
    background: #fff;
    border: 1px solid #ccc;
    padding: 12px;
}
"""

def make_source_viewer(root, rel_path, target_path, is_old, file_hash, content):
    """Generate a clean HTML viewer for an individual source file."""
    title = f"{'Original (Old)' if is_old else 'Evolved (New)'} Source: {target_path}"
    out_dir = root / f"views/sources/{'old' if is_old else 'new'}"
    out_dir.mkdir(parents=True, exist_ok=True)
    out_file = out_dir / f"{file_hash[:20]}.html"

    lines = content.splitlines()
    formatted_lines = []
    for idx, line in enumerate(lines, 1):
        formatted_lines.append(f'<span style="color:#888;display:inline-block;width:45px;text-align:right;margin-right:12px;user-select:none;">{idx:4d}</span>{html.escape(line)}')
    code_html = "\n".join(formatted_lines)

    body = f"""<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>{html.escape(title)}</title>
<style>{ACADEMIC_CSS}</style>
</head>
<body>
<div class="academic-nav">
  <a href="../../../index.html#sources">&larr; Back to Source Index</a>
  <a href="../../../index.html">Main Review Page</a>
  <a href="../../../graphs.html">Visualizations</a>
  <a href="../../../diffs/{file_hash[:20]}.html">Compare Side-by-Side Diff</a>
  <a href="../../../{rel_path}">Raw File</a>
</div>

<h1>{html.escape(title)}</h1>
<p><strong>File Repository Path:</strong> <code>{html.escape(target_path)}</code></p>
<p><strong>Total Lines:</strong> {len(lines)} &middot; <strong>Format:</strong> Formatted HTML View (&middot; <a href="../../../{rel_path}">Download Raw Source File</a>)</p>

<div class="code-view">
{code_html}
</div>

<p style="margin-top:20px;"><a href="../../../index.html#sources">&larr; Back to Source Index</a></p>
</body>
</html>
"""
    out_file.write_text(body)
    return str(out_file.relative_to(root))


def build_views(root, index):
    """Create HTML viewers for all files in source_file_index.csv."""
    EMPTY_SHA = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
    views = {}
    for item in index:
        fhash = item["file_hash"]
        target = item["new_repo_path"]

        # Old file
        if item["old_sha256"] != EMPTY_SHA:
            old_p = root / item["old_file"]
            if old_p.exists():
                content = old_p.read_text(errors="replace")
                old_view = make_source_viewer(root, item["old_file"], target, True, fhash, content)
                views[(fhash, "old")] = old_view

        # New file
        new_p = root / item["new_file"]
        if new_p.exists():
            content = new_p.read_text(errors="replace")
            new_view = make_source_viewer(root, item["new_file"], target, False, fhash, content)
            views[(fhash, "new")] = new_view

    return views


def build_graphs_page(root, analysis):
    """Generate dedicated graphs.html page."""
    captions = {
        'improvement_distribution.svg': ('Figure 1: Improvement Distribution', 'Distribution of timing improvements across all 3,500 candidate variants in WNS and TNS.'),
        'improvement_percentiles.svg': ('Figure 2: Improvement Percentiles (P1 to P99)', 'Cumulative percentiles showing population boundaries: P1 at 0.01%, Median at 0.72%, P95 at 4.38%, and P99 at 4.88%.'),
        'wns_tns_scatter.svg': ('Figure 3: WNS vs. TNS Trade-off Scatter', 'Scatter distribution comparing Worst Negative Slack (WNS) versus Total Negative Slack (TNS) improvements across generated parameter candidates.'),
        'source_change_concentration.svg': ('Figure 4: Physical Source Code Changes by File', 'Physical count of added and removed lines of code across production source files in the repository, led by SinkClustering_new.cpp and SetupLegacyBase_new.cc.'),
        'changed_policy_fields.svg': ('Figure 5: Policy Field Modification Frequency', 'Frequency of policy configuration parameters modified by candidate patches, exploring tuning across loads, spatial modes, density weights, and DP budgets.'),
        'highest_labeled_candidates.svg': ('Figure 6: Top-Ranking Candidates Under Evaluation Function', 'Composite score distribution for the top 20 candidate configurations under the study scoring metric.')
    }

    figs_html = []
    for gpath in analysis['graphs']:
        p = Path(gpath)
        title, desc = captions.get(p.name, (p.stem.replace('_', ' ').title(), ''))
        figs_html.append(f"""
<figure class="academic-fig" id="{p.stem}">
  <h3>{html.escape(title)}</h3>
  <a href="{html.escape(gpath)}"><img src="{html.escape(gpath)}" alt="{html.escape(title)}"></a>
  <figcaption class="academic-cap">
    <strong>{html.escape(title)}:</strong> {html.escape(desc)}
    <br><span class="muted"><a href="{html.escape(gpath)}">Open full SVG vector image</a></span>
  </figcaption>
</figure>
""")

    stats_rows = []
    for entry in analysis['summaries']:
        cells = [html.escape(entry['metric'])] + [f'{entry[k]:.4f}' for k in ['mean', 'median', 'stddev', 'p1', 'p95', 'p99']]
        cells.append(f'[{entry["modal_bin_low"]:.2f}, {entry["modal_bin_high"]:.2f})')
        stats_rows.append('<tr>' + ''.join(f'<td>{v}</td>' for v in cells) + '</tr>')

    body = f"""<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>OpenROAD Code Evolution — Visualizations & Graphs</title>
<style>{ACADEMIC_CSS}</style>
</head>
<body>
<div class="academic-nav">
  <a href="index.html">&larr; Back to Main Study Page</a>
  <a href="index.html#statistics">Statistics Table</a>
  <a href="index.html#sources">Source Code Index</a>
  <a href="index.html#candidates">Candidate Explorer</a>
  <a href="README.md">Methodology (README)</a>
  <a href="statistics/summary.csv">Summary CSV</a>
</div>

<h1>Visualizations & Empirical Distributions</h1>
<p class="muted">OpenROAD Algorithmic Evolution Study &middot; Figure Portfolio</p>

<h2>Table of Figures</h2>
<ul>
  <li><a href="#improvement_distribution">Figure 1: Improvement Distribution</a></li>
  <li><a href="#improvement_percentiles">Figure 2: Improvement Percentiles (P1 to P99)</a></li>
  <li><a href="#wns_tns_scatter">Figure 3: WNS vs. TNS Trade-off Scatter</a></li>
  <li><a href="#source_change_concentration">Figure 4: Physical Source Code Changes by File</a></li>
  <li><a href="#changed_policy_fields">Figure 5: Policy Field Modification Frequency</a></li>
  <li><a href="#highest_labeled_candidates">Figure 6: Top-Ranking Candidates Under Evaluation Function</a></li>
</ul>

<h2>Descriptive Statistics Summary</h2>
<table class="academic-table">
  <thead>
    <tr><th>Metric</th><th>Mean</th><th>Median</th><th>Std dev</th><th>P1</th><th>P95</th><th>P99</th><th>Modal interval</th></tr>
  </thead>
  <tbody>
    {''.join(stats_rows)}
  </tbody>
</table>

<h2>Empirical Distribution Figures</h2>
{''.join(figs_html)}

<p style="margin-top:30px;"><a href="index.html">&larr; Back to Main Study Page</a></p>
</body>
</html>
"""
    (root / "graphs.html").write_text(body)


def build_index_page(root, analysis, candidates, index, views):
    """Generate the clean, academic index.html page."""
    summary = {row['metric']: row for row in analysis['summaries']}
    wns = summary['wns_impact_pct']
    tns = summary['tns_impact_pct']
    runtime = summary['runtime_delta_s']
    production = [row for row in index if row['category'] == 'production source']

    stats_rows = []
    for entry in analysis['summaries']:
        cells = [html.escape(entry['metric'])] + [f'{entry[k]:.4f}' for k in ['mean', 'median', 'stddev', 'p1', 'p95', 'p99']]
        cells.append(f'[{entry["modal_bin_low"]:.2f}, {entry["modal_bin_high"]:.2f})')
        stats_rows.append('<tr>' + ''.join(f'<td>{v}</td>' for v in cells) + '</tr>')

    EMPTY_SHA = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"

    source_rows = []
    for item in index:
        fhash = item["file_hash"]
        target = item["new_repo_path"]
        cat = item["category"]
        added = item["lines_added"]
        removed = item["lines_removed"]

        if item["old_sha256"] == EMPTY_SHA:
            old_html = '<span class="muted">None (new file)</span>'
        else:
            view_path = views.get((fhash, "old"), item["old_file"])
            old_html = f'<a href="{view_path}">View</a> (<a href="{item["old_file"]}">raw</a>)'

        new_view_path = views.get((fhash, "new"), item["new_file"])
        new_html = f'<a href="{new_view_path}">View</a> (<a href="{item["new_file"]}">raw</a>)'

        diff_link = f'<a href="{item["diff_page"]}">Compare Diff</a>'
        patch_link = f'<a href="{item["full_patch"]}">Patch</a>'

        source_rows.append(f'<tr><td><code>{html.escape(target)}</code></td><td>{cat}</td><td>+{added} / &minus;{removed}</td><td>{old_html} &middot; {new_html} &middot; {diff_link} &middot; {patch_link}</td></tr>')

    best = analysis['highest_labeled_candidate']
    packed_candidates = json.dumps(candidates).replace('<', '\\u003c')

    body = f"""<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>OpenROAD Algorithmic Evolution &mdash; Source & Evaluation Study</title>
<style>{ACADEMIC_CSS}</style>
</head>
<body>

<h1>OpenROAD Algorithmic Code Evolution &mdash; Code Implementations & Evaluation Study</h1>
<p class="muted">
  <strong>Repository:</strong> OpenROAD EDA Evolution Suite &middot; 
  <strong>Branch:</strong> <code>eda/learning_draft_final_evolved_code_openroad_v2</code> &middot;
  <strong>Checkout:</strong> <code>suite/external/OpenROAD</code>
</p>

<div class="academic-nav">
  <a href="#statistics">Statistics</a>
  <a href="#graphs-ref">Visualizations (Separate Page)</a>
  <a href="#sources">Old / New Source Index</a>
  <a href="#candidates">Candidate Variants</a>
  <a href="README.md">Methodology (README)</a>
  <a href="SOURCE_INDEX.md">Source Index (MD)</a>
  <a href="data/all_code_changes.csv">All Changes CSV</a>
</div>

<p>
  This directory presents concrete C++ algorithmic optimizations integrated directly into OpenROAD's Clock Tree Synthesis (<code>src/cts/</code>)
  and Timing Resizing (<code>src/rsz/</code>) engines. Below are the complete source diffs, integrated micro-kernels, candidate policy parameter variations,
  and comprehensive performance metrics.
</p>

<table class="summary-grid">
  <tr>
    <td>
      <span class="muted">Policy Variants</span>
      <strong>{len(candidates):,}</strong>
    </td>
    <td>
      <span class="muted">Mean WNS Impact</span>
      <strong>{wns['mean']:.3f}%</strong>
    </td>
    <td>
      <span class="muted">Mean TNS Impact</span>
      <strong>{tns['mean']:.3f}%</strong>
    </td>
    <td>
      <span class="muted">Production Sources</span>
      <strong>{len(production)}</strong>
    </td>
  </tr>
</table>

<h2 id="statistics">1. All-Candidate Descriptive Statistics</h2>
<p>
  Summary statistics derived across the 3,500 candidate policy evaluations.
  Percentiles are interpolated using <code>(n - 1) &times; p / 100</code>.
  Modal intervals indicate the most populated 0.25-point band.
</p>
<div class="scroll">
<table class="academic-table">
  <thead>
    <tr><th>Metric</th><th>Mean</th><th>Median</th><th>Std dev</th><th>P1</th><th>P95</th><th>P99</th><th>Modal interval</th></tr>
  </thead>
  <tbody>
    {''.join(stats_rows)}
  </tbody>
</table>
</div>
<p>
  <a href="statistics/summary.csv">Download Statistics CSV (summary.csv)</a> &middot;
  <a href="statistics/analysis.json">Complete Analysis JSON (analysis.json)</a>
</p>

<h2 id="graphs-ref">2. Visualizations and Empirical Distribution Graphs</h2>
<p>
  All detailed visual plots, trade-off distributions, and change concentration figures are presented on a dedicated page:
</p>
<p style="font-size: 15px; margin: 14px 0;">
  &rarr; <strong><a href="graphs.html">View Graphical Analysis & Figure Portfolio (graphs.html)</a></strong>
</p>
<p class="muted">
  Figures on the graphs page include:
  Figure 1 (Improvement Distribution),
  Figure 2 (Percentile Progression P1&ndash;P99),
  Figure 3 (WNS vs. TNS Trade-off Scatter),
  Figure 4 (Physical Line Changes by Source File),
  Figure 5 (Policy Field Modification Frequencies), and
  Figure 6 (Score Profile of Top Candidates).
</p>

<h2 id="sources">3. Exact Old / New Source Code Index</h2>
<p>
  All touched files and integrated micro-kernels are indexed below.
  Click <strong>View</strong> to read complete source files in an HTML viewer with line numbers,
  <strong>raw</strong> to download the unformatted code,
  <strong>Compare Diff</strong> for side-by-side colorized differences, or
  <strong>Patch</strong> for the unified patch.
</p>

<div class="tools">
  <input id="source-search" placeholder="Filter by file path or module...">
  <span id="source-count" class="muted"></span>
</div>

<div class="scroll">
<table class="academic-table">
  <thead>
    <tr><th>Source Repository Path</th><th>Category</th><th>Lines &plus; / &minus;</th><th>Available Views & Links</th></tr>
  </thead>
  <tbody id="source-rows">
    {''.join(source_rows)}
  </tbody>
</table>
</div>
<p>
  <a href="data/source_file_index.csv">Exact Source File Index CSV</a> &middot;
  <a href="data/applied_changes.csv">Applied Hunk Hashes CSV</a>
</p>

<h2 id="candidates">4. Proposed Policy Variants Explorer</h2>
<p>
  Each variant represents a complete alternative configuration header for Clock Tree Synthesis and Resizer policies.
  Highest score candidate: <code>{best['change_hash'][:16]}</code> (Score: {best['overall_score']}) &mdash; 
  <a href="{best['new_path']}">Open Variant Header</a>.
</p>

<div class="tools">
  <input id="candidate-search" placeholder="Search by hash, field, or iteration...">
  <select id="candidate-sort">
    <option value="iteration">Sort by: Agent Iteration</option>
    <option value="score">Sort by: Highest Overall Score</option>
    <option value="wns">Sort by: Highest WNS Impact</option>
    <option value="tns">Sort by: Highest TNS Impact</option>
  </select>
  <button id="previous">&larr; Previous</button>
  <button id="next">Next &rarr;</button>
  <span id="candidate-count" class="muted"></span>
</div>

<div class="scroll">
<table class="academic-table">
  <thead>
    <tr><th>Candidate Hash / Iteration</th><th>Modified Policy Fields</th><th>WNS Impact %</th><th>TNS Impact %</th><th>Composite Score</th><th>Header & Patch</th></tr>
  </thead>
  <tbody id="candidate-rows"></tbody>
</table>
</div>

<h2>5. Local Verification & Reproducibility</h2>
<pre>
make stats     # Compute mean, median, std dev, P1-P99 and modal interval from raw CSV
make graphs    # Regenerate standalone SVG figures and statistical analysis
make verify    # Verify SHA-256 checksums, candidate integrity, and all HTML links
make test      # Compile and run integrated-kernel regression tests in OpenROAD
</pre>

<script>
const candidates = {packed_candidates};
const byId = id => document.getElementById(id);
const escapeText = value => String(value).replace(/[&<>"']/g, c => ({{'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}}[c]));
let pageNumber = 0;
const pageSize = 50;

function renderCandidates() {{
  const query = byId('candidate-search').value.toLowerCase();
  let data = candidates.filter(r => (r.change_hash + ' ' + r.changed_fields + ' ' + r.agent_iteration).toLowerCase().includes(query));
  const sortKey = {{score:'overall_score', wns:'wns_impact_pct', tns:'tns_impact_pct'}}[byId('candidate-sort').value];
  if (sortKey) {{
    data.sort((a,b) => Number(b[sortKey]) - Number(a[sortKey]));
  }} else {{
    data.sort((a,b) => Number(a.agent_iteration) - Number(b.agent_iteration));
  }}
  const totalPages = Math.max(1, Math.ceil(data.length / pageSize));
  pageNumber = Math.max(0, Math.min(pageNumber, totalPages - 1));
  const visible = data.slice(pageNumber * pageSize, (pageNumber + 1) * pageSize);
  byId('candidate-rows').innerHTML = visible.map(r => `<tr>
    <td><code>${{escapeText(r.change_hash.slice(0,14))}}</code><br><span class="muted">iteration ${{r.agent_iteration}}</span></td>
    <td>${{escapeText(r.changed_fields.replaceAll(';', ', '))}}</td>
    <td>${{Number(r.wns_impact_pct).toFixed(4)}}</td>
    <td>${{Number(r.tns_impact_pct).toFixed(4)}}</td>
    <td>${{Number(r.overall_score).toFixed(4)}}</td>
    <td><a href="${{r.old_path}}">Base</a> &middot; <a href="${{r.new_path}}">Variant</a> &middot; <a href="${{r.patch_path}}">Patch</a></td>
  </tr>`).join('');
  byId('candidate-count').textContent = `${{data.length}} matching &middot; page ${{pageNumber + 1}} of ${{totalPages}}`;
}}

for (const id of ['candidate-search', 'candidate-sort']) {{
  byId(id).addEventListener('input', () => {{ pageNumber = 0; renderCandidates(); }});
}}
byId('previous').onclick = () => {{ if (pageNumber > 0) {{ pageNumber--; renderCandidates(); }} }};
byId('next').onclick = () => {{ pageNumber++; renderCandidates(); }};

function filterSources() {{
  const query = byId('source-search').value.toLowerCase();
  let count = 0;
  for (const row of byId('source-rows').rows) {{
    const match = row.textContent.toLowerCase().includes(query);
    row.style.display = match ? '' : 'none';
    if (match) count++;
  }}
  byId('source-count').textContent = `${{count}} files matching`;
}}
byId('source-search').oninput = filterSources;

filterSources();
renderCandidates();
</script>

</body>
</html>
"""
    (root / "index.html").write_text(body)


def update_source_index_md(root, index, views):
    """Update SOURCE_INDEX.md with working links."""
    EMPTY_SHA = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
    lines = [
        "# Exact old/new source file index",
        "",
        "Use **Compare** for side-by-side diffs. **View (HTML)** opens full source in browser; **raw** downloads original code.",
        ""
    ]
    for item in index:
        fhash = item["file_hash"]
        target = item["new_repo_path"]
        added = item["lines_added"]
        removed = item["lines_removed"]
        diff_page = item["diff_page"]
        full_patch = item["full_patch"]

        if item["old_sha256"] == EMPTY_SHA:
            old_str = "Old: *None (new file)*"
        else:
            old_view = views.get((fhash, "old"), item["old_file"])
            old_str = f"[Old (HTML)]({old_view}) ([raw]({item['old_file']}))"

        new_view = views.get((fhash, "new"), item["new_file"])
        new_str = f"[New (HTML)]({new_view}) ([raw]({item['new_file']}))"

        lines.append(f"- **{target}**: {old_str} · {new_str} · [Compare]({diff_page}) · [Patch]({full_patch}) (+{added}/-{removed})")

    (root / "SOURCE_INDEX.md").write_text("\n".join(lines) + "\n")


def update_diff_pages(root, index, views):
    """Update diff HTML headers to point to working HTML viewers as well."""
    EMPTY_SHA = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
    for item in index:
        diff_p = root / item["diff_page"]
        if not diff_p.exists():
            continue
        text = diff_p.read_text(errors="replace")
        fhash = item["file_hash"]

        if item["old_sha256"] == EMPTY_SHA:
            old_part = '<span class="muted">Original source: None (new file)</span>'
        else:
            old_v = views.get((fhash, "old"), item["old_file"])
            old_part = f'<a href="../{old_v}">Full original source (View)</a> (<a href="../{item["old_file"]}">raw</a>)'

        new_v = views.get((fhash, "new"), item["new_file"])
        new_part = f'<a href="../{new_v}">Full new source (View)</a> (<a href="../{item["new_file"]}">raw</a>)'

        old_pattern_start = '<p><a href="../sources/old/'
        idx = text.find(old_pattern_start)
        if idx != -1:
            end_idx = text.find('</p>', idx)
            if end_idx != -1:
                replacement = f'<p>{old_part} &middot; {new_part}</p>'
                text = text[:idx] + replacement + text[end_idx+4:]
                diff_p.write_text(text)


def update_checksums(root):
    """Recalculate CHECKSUMS.json for tracked directories."""
    checksums = {}
    for directory in ['data', 'sources', 'candidate_code', 'patches', 'views']:
        dir_p = root / directory
        if not dir_p.exists():
            continue
        for path in sorted(dir_p.rglob('*')):
            if path.is_file():
                checksums[str(path.relative_to(root))] = hashlib.sha256(path.read_bytes()).hexdigest()
    (root / 'CHECKSUMS.json').write_text(json.dumps(checksums, indent=2) + '\n')


def refresh(root, analysis, rows, index):
    """Main entrypoint called by study_stats.py and build_final.py."""
    root_p = Path(root)
    views = build_views(root_p, index)
    build_graphs_page(root_p, analysis)
    build_index_page(root_p, analysis, rows, index, views)
    update_source_index_md(root_p, index, views)
    update_diff_pages(root_p, index, views)
    update_checksums(root_p)
