#!/usr/bin/env python3
"""Build a self-contained, browsable handoff folder with exact code and data."""
import csv
import difflib
import hashlib
import html
import json
import inspect
import re
from pathlib import Path
import shutil
import sys
sys.path.insert(0, str(Path(__file__).resolve().parent))
from study_stats import analyze, read_csv, write_csv
from render_graphs import render

ROOT = Path(__file__).resolve().parents[2]
HOME = ROOT / 'learning_evolution'
FINAL = ROOT.parents[1] / 'OPENROAD_EVOLUTION_FINAL'
CSS = '''
:root{font-family:Arial,sans-serif;color:#162939;background:#f5f7f9}body{margin:0}
main{max-width:1200px;margin:auto;padding:32px}h1{font-size:30px;margin:8px 0 12px}
h2{font-size:21px;margin-top:36px}p{line-height:1.55}a{color:#215e8c}
nav{display:flex;gap:20px;flex-wrap:wrap;margin:24px 0;border-bottom:1px solid #ccd6df;padding-bottom:14px}
.notice{padding:14px 18px;border-left:4px solid #b8753a;background:#faf4e9;line-height:1.5}
.metrics{display:grid;grid-template-columns:repeat(4,minmax(0,1fr));gap:24px;margin:28px 0}
.metric strong{display:block;font-size:30px;margin-top:8px}.muted{color:#526575;font-size:13px}
.graphs{display:grid;grid-template-columns:repeat(2,minmax(0,1fr));gap:22px}
figure{margin:0;background:white;border:1px solid #dce3e9;padding:8px}figure img{width:100%;height:auto}
figcaption{padding:10px;font-size:13px;color:#526575}table{width:100%;border-collapse:collapse;background:white;font-size:13px}
th,td{padding:11px 10px;border-bottom:1px solid #dce3e9;text-align:left;vertical-align:top}
th{background:#eaf0f5;font-weight:600;position:sticky;top:0}code{font-size:12px;overflow-wrap:anywhere}
.scroll{max-height:600px;overflow:auto;border:1px solid #dce3e9}input,select,button{font:inherit;padding:9px;border:1px solid #b9c6d0;background:white;border-radius:3px}
input{min-width:300px}button{cursor:pointer}.tools{display:flex;gap:12px;align-items:center;margin:12px 0;flex-wrap:wrap}
pre{white-space:pre-wrap;word-break:break-word;background:white;padding:20px;border:1px solid #dce3e9;line-height:1.45}
.diff{font-family:monospace;font-size:12px;width:auto;min-width:100%}.diff td{padding:3px 6px;white-space:pre}.diff_header{background:#eef2f5}
.diff_add{background:#dcecdf}.diff_sub{background:#f3deda}.diff_chg{background:#f2e8c7}
@media(max-width:800px){main{padding:18px}.graphs,.metrics{grid-template-columns:1fr 1fr}input{min-width:180px}}
'''


def page(title, body):
    return '<!doctype html><html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>' + html.escape(title) + '</title><style>' + CSS + '</style></head><body>' + body + '</body></html>\n'


def copy_file(source, relative):
    destination = FINAL / relative
    destination.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(source, destination)
    return str(relative)


def source_bundle(applied):
    pairs = {pair['new']: pair for pair in json.loads((HOME / 'source_pairs.json').read_text())}
    index = []
    for target in sorted({row['target_path'] for row in applied}):
        blocks = [row for row in applied if row['target_path'] == target]
        original = pairs.get(target, {}).get('original', target)
        before_path = blocks[0]['old_path']
        before = (ROOT / before_path).read_text() if before_path else ''
        after = (ROOT / target).read_text()
        old_relative = Path('sources/old') / original
        new_relative = Path('sources/new') / target
        for relative, content in [(old_relative, before), (new_relative, after)]:
            destination = FINAL / relative
            destination.parent.mkdir(parents=True, exist_ok=True)
            destination.write_text(content)
        file_hash = hashlib.sha256((target + '\n' + before + '\n' + after).encode()).hexdigest()
        diff_relative = Path('diffs') / (file_hash[:20] + '.html')
        diff = difflib.HtmlDiff(tabsize=2, wrapcolumn=100).make_table(
            before.splitlines(), after.splitlines(),
            fromdesc=html.escape('OLD: ' + (before_path or '(new file)')),
            todesc=html.escape('NEW: ' + target), context=True, numlines=5)
        body = '<main><a href="../index.html#sources">Back to source index</a><h1>' + html.escape(Path(target).name) + '</h1>'
        body += '<p><a href="../' + old_relative.as_posix() + '">Full original source</a> · <a href="../' + new_relative.as_posix() + '">Full new source</a></p>'
        body += '<p class="muted">Context view shows changed regions. Follow the source links for the complete files. An empty original denotes a newly added file.</p><div style="overflow:auto">' + diff + '</div></main>'
        (FINAL / diff_relative).write_text(page('Old / new: ' + target, body))
        raw_patch = ''.join(difflib.unified_diff(before.splitlines(keepends=True), after.splitlines(keepends=True), fromfile='a/' + original, tofile='b/' + target))
        patch_relative = Path('patches/files') / (file_hash + '.patch')
        (FINAL / patch_relative).write_text(raw_patch)
        index.append(dict(file_hash=file_hash, category=('production source' if Path(target).suffix in {'.cpp', '.cc', '.h', '.hh'} else 'build integration') if target.startswith('src/') else 'tests / tooling',
                          original_path=original, old_repo_path=before_path, new_repo_path=target,
                          old_file=old_relative.as_posix(), new_file=new_relative.as_posix(),
                          diff_page=diff_relative.as_posix(), full_patch=patch_relative.as_posix(),
                          lines_added=sum(int(row['lines_added']) for row in blocks),
                          lines_removed=sum(int(row['lines_removed']) for row in blocks),
                          block_hashes=';'.join(row['change_hash'] for row in blocks),
                          old_sha256=hashlib.sha256(before.encode()).hexdigest(),
                          new_sha256=hashlib.sha256(after.encode()).hexdigest()))
    write_csv(FINAL / 'data/source_file_index.csv', index)
    return index


def export_data():
    candidates = read_csv(HOME / 'dataset/changes.csv')
    applied = read_csv(HOME / 'dataset/applied_changes.csv')
    index = source_bundle(applied)
    source_lookup = {row['new_repo_path']: row for row in index}
    exported = []
    shared_old = copy_file(HOME / 'dataset/PolicyConfig_old.h', Path('candidate_code/LearningPolicyConfig_old.h'))
    for row in candidates:
        item = dict(row)
        item['repo_old_path'] = item['old_path']
        item['repo_new_path'] = item['new_path']
        item['old_path'] = shared_old
        item['new_path'] = copy_file(ROOT / row['new_path'], Path('candidate_code') / Path(row['new_path']).name)
        item['patch_path'] = copy_file(ROOT / row['patch_path'], Path('patches/candidates') / Path(row['patch_path']).name)
        exported.append(item)
    for row in applied:
        source = source_lookup[row['target_path']]
        row['repo_old_path'], row['repo_new_path'] = row['old_path'], row['new_path']
        row['old_path'], row['new_path'] = source['old_file'], source['new_file']
        row['diff_page'] = source['diff_page']
        row['patch_path'] = copy_file(ROOT / row['patch_path'], Path('patches/applied_blocks') / Path(row['patch_path']).name)
    write_csv(FINAL / 'data/candidates.csv', exported)
    write_csv(FINAL / 'data/applied_changes.csv', applied)
    fields = sorted(set().union(*(row.keys() for row in exported + applied)))
    all_rows = []
    for kind, rows in [('proposed_policy_variant', exported), ('applied_source_block', applied)]:
        for row in rows:
            all_rows.append({'record_kind': kind, **{field: row.get(field, '') for field in fields}})
    write_csv(FINAL / 'data/all_code_changes.csv', all_rows)
    (FINAL / 'data/all_code_changes.jsonl').write_text(''.join(json.dumps(row) + '\n' for row in all_rows))
    copy_file(HOME / 'dataset/provenance.json', Path('data/provenance.json'))
    copy_file(HOME / 'embedded_kernels.json', Path('data/embedded_kernels.json'))
    return exported, applied, index


def dashboard(analysis, rows, index):
    summary = {row['metric']: row for row in analysis['summaries']}
    wns, tns = summary['simulated_wns_impact_pct'], summary['simulated_tns_impact_pct']
    production = [row for row in index if row['category'] == 'production source']
    body = '<main><div class="muted">OPENROAD / SOURCE EVOLUTION / STUDY HANDOFF</div><h1>Code changes and study statistics</h1>'
    body += '<p>One folder for the exact old/new source files, applied change hashes, proposed policy variants, descriptive statistics and graphs.</p>'
    body += '<div class="notice"><strong>Data provenance:</strong> source edits are real; timing and effectiveness labels are simulated. CSV averages describe the study dataset, not expected real OpenROAD performance. The full OpenROAD build and flow have not run.</div>'
    body += '<nav><a href="#summary">Statistics</a><a href="#graphs">Graphs</a><a href="#sources">Old / new code</a><a href="#candidates">Candidate browser</a><a href="README.md">Commands & methodology</a><a href="data/all_code_changes.csv">All changes CSV</a></nav>'
    body += '<section class="metrics">'
    for label, value in [('Proposed policy variants', f'{len(rows):,}'), ('Mean WNS label', f'{wns["mean"]:.3f}%'), ('Mean TNS label', f'{tns["mean"]:.3f}%'), ('Production source files in bundle', str(len(production)))]:
        body += '<div class="metric"><span class="muted">' + label + '</span><strong>' + value + '</strong></div>'
    body += '</section><h2 id="summary">All-candidate descriptive statistics</h2><p class="muted">Percentiles use linear interpolation. “Mode” is the most populated 0.25-point interval for percentages, rather than an arbitrary exact mode for continuous values.</p><div class="scroll"><table><thead><tr><th>Label</th><th>Mean</th><th>Median</th><th>Std dev</th><th>P1</th><th>P95</th><th>P99</th><th>Modal interval</th></tr></thead><tbody>'
    for entry in analysis['summaries']:
        cells = [html.escape(entry['metric'])] + [f'{entry[key]:.4f}' for key in ['mean', 'median', 'stddev', 'p1', 'p95', 'p99']]
        cells.append(f'[{entry["modal_bin_low"]:.2f}, {entry["modal_bin_high"]:.2f})')
        body += '<tr>' + ''.join('<td>' + value + '</td>' for value in cells) + '</tr>'
    body += '</tbody></table></div><p><a href="statistics/summary.csv">Download statistics CSV</a> · <a href="statistics/analysis.json">Complete analysis JSON</a></p>'
    body += '<h2 id="graphs">Graphs for inspection and slides</h2><div class="graphs">'
    captions = {
        'improvement_distribution.svg': 'Most labels are near zero; the rare 4–5% cluster comes from the specified generator.',
        'improvement_percentiles.svg': 'P1 through P99 of the complete candidate label population.',
        'wns_tns_scatter.svg': 'Label trade-offs, not measured causal effects of code.',
        'source_change_concentration.svg': 'Actual added/removed lines by production source file; separate from impact labels.',
        'highest_labeled_candidates.svg': 'Highest fictional scores; these do not identify a real optimal code change.',
        'changed_policy_fields.svg': 'Which shared policy fields are edited by the candidate patches.',
    }
    for path in analysis['graphs']:
        body += '<figure><a href="' + path + '"><img src="' + path + '" alt="' + html.escape(Path(path).stem.replace('_', ' ')) + '"></a><figcaption>' + captions[Path(path).name] + '</figcaption></figure>'
    body += '</div><h2 id="sources">Exact old / new source index</h2><p>Click <strong>Compare</strong> for a side-by-side code diff, or open either complete source file. Algorithms are embedded in the real OpenROAD translation units. The study policy headers are only configurations.</p>'
    body += '<div class="tools"><input id="source-search" placeholder="Filter by source path or category"><span id="source-count"></span></div><div class="scroll"><table><thead><tr><th>Source path</th><th>Kind</th><th>+ / − lines</th><th>Files</th></tr></thead><tbody id="source-rows">'
    for item in index:
        body += '<tr><td><code>' + html.escape(item['new_repo_path']) + '</code></td><td>' + item['category'] + '</td><td>+' + str(item['lines_added']) + ' / −' + str(item['lines_removed']) + '</td><td><a href="' + item['old_file'] + '">Old</a> · <a href="' + item['new_file'] + '">New</a> · <a href="' + item['diff_page'] + '">Compare</a> · <a href="' + item['full_patch'] + '">Patch</a></td></tr>'
    body += '</tbody></table></div><p><a href="data/source_file_index.csv">Exact source-file index CSV</a> · <a href="data/applied_changes.csv">Applied block hashes CSV</a></p>'
    best = analysis['highest_labeled_candidate']
    body += '<h2 id="candidates">Proposed policy variants</h2><p>A variant is one complete alternative configuration header. A patch records the lines changed to produce it. The 3,500 variants are alternatives, not all installed simultaneously.</p>'
    body += '<p>Highest simulated score: <code>' + best['change_hash'][:16] + '</code> (' + best['simulated_overall_score'] + '). <a href="' + best['new_path'] + '">Open candidate code</a>. This is a label ranking, not a verified optimum.</p>'
    body += '<div class="tools"><input id="candidate-search" placeholder="Filter by hash, field or iteration"><select id="candidate-sort"><option value="iteration">Iteration</option><option value="score">Highest simulated score</option><option value="wns">Highest WNS label</option><option value="tns">Highest TNS label</option></select><button id="previous">Previous</button><button id="next">Next</button><span id="candidate-count"></span></div>'
    body += '<div class="scroll"><table><thead><tr><th>Hash / iteration</th><th>Edited fields</th><th>WNS %</th><th>TNS %</th><th>Score</th><th>Source</th></tr></thead><tbody id="candidate-rows"></tbody></table></div>'
    body += '<h2>Run locally</h2><pre>make stats     # mean, median, std dev, P1–P99 and binned mode\nmake graphs    # regenerate six SVG graphs and statistics\nmake verify    # verify source hashes, dataset hashes and local links\nmake report    # print the CSV-derived result summary\nmake test      # run integrated-source kernel checks in the original checkout</pre><p class="muted">Statistics, graphs, data and source viewers are self-contained. Kernel compilation requires the original OpenROAD checkout. No network is needed to browse this folder.</p></main>'
    packed = json.dumps(rows).replace('<', '\\u003c')
    body += '<script>const candidates=' + packed + ';\n' + '''
const byId=id=>document.getElementById(id);
const escapeText=value=>String(value).replace(/[&<>"']/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));
let pageNumber=0; const pageSize=50;
function renderCandidates(){
 const query=byId('candidate-search').value.toLowerCase();
 let data=candidates.filter(r=>(r.change_hash+' '+r.changed_fields+' '+r.agent_iteration).toLowerCase().includes(query));
 const key={score:'simulated_overall_score',wns:'simulated_wns_impact_pct',tns:'simulated_tns_impact_pct'}[byId('candidate-sort').value];
 data.sort((a,b)=>key?Number(b[key])-Number(a[key]):Number(a.agent_iteration)-Number(b.agent_iteration));
 pageNumber=Math.max(0,Math.min(pageNumber,Math.max(0,Math.ceil(data.length/pageSize)-1)));
 const visible=data.slice(pageNumber*pageSize,(pageNumber+1)*pageSize);
 byId('candidate-rows').innerHTML=visible.map(r=>`<tr><td><code>${escapeText(r.change_hash.slice(0,14))}</code><br>iteration ${r.agent_iteration}</td><td>${escapeText(r.changed_fields.replaceAll(';',', '))}</td><td>${Number(r.simulated_wns_impact_pct).toFixed(4)}</td><td>${Number(r.simulated_tns_impact_pct).toFixed(4)}</td><td>${Number(r.simulated_overall_score).toFixed(4)}</td><td><a href="${r.old_path}">Old</a> · <a href="${r.new_path}">Variant</a> · <a href="${r.patch_path}">Patch</a></td></tr>`).join('');
 byId('candidate-count').textContent=`${data.length} matching · page ${pageNumber+1} of ${Math.max(1,Math.ceil(data.length/pageSize))}`;
}
for(const id of ['candidate-search','candidate-sort'])byId(id).addEventListener('input',()=>{pageNumber=0;renderCandidates()});
byId('previous').onclick=()=>{pageNumber--;renderCandidates()};byId('next').onclick=()=>{pageNumber++;renderCandidates()};
function filterSources(){const query=byId('source-search').value.toLowerCase();let count=0;for(const row of byId('source-rows').rows){row.hidden=!row.textContent.toLowerCase().includes(query);if(!row.hidden)count++}byId('source-count').textContent=count+' files';}
byId('source-search').oninput=filterSources;filterSources();renderCandidates();
''' + '</script>'
    (FINAL / 'index.html').write_text(page('OpenROAD code evolution — final study bundle', body))


def documentation(analysis, index):
    stats = {row['metric']: row for row in analysis['summaries']}
    text = ['# OpenROAD evolution: final review folder', '',
            'Open [index.html](index.html) for the offline dashboard, graphs, source comparisons and candidate browser.', '',
            '**Provenance:** code edits are real; candidate impact labels are simulated. Averages describe this CSV, not an expected real-world tool improvement.', '',
            '## Commands from this folder', '',
            '```sh', 'make stats', 'make graphs', 'make report', 'make verify', 'make test', '```', '',
            '`make stats`, `graphs`, `report` and `verify` need only Python 3 and the bundled files.',
            '`make test` requires the original OpenROAD checkout and a C++20 compiler.', '',
            '## CSV-derived summary', '']
    for field in ['simulated_wns_impact_pct', 'simulated_tns_impact_pct', 'combined_timing_label_pct']:
        entry = stats[field]
        text.append(f'- {field}: mean {entry["mean"]:.4f}%, median {entry["median"]:.4f}%, P1 {entry["p1"]:.4f}%, P99 {entry["p99"]:.4f}%.')
    text += ['', 'The all-candidate arithmetic mean is the primary summary; filtering accepted/high-scoring rows would bias it upward.',
             'Percentiles interpolate at `(n - 1) * p / 100`. Standard deviation is the sample statistic.',
             'Mode is reported as the most populated fixed-width interval (0.25 percentage points for timing labels), not an unstable exact floating-point mode.', '',
             '## What each directory contains', '',
             '- `data/all_code_changes.csv`: combined applied blocks and proposed variants; record_kind distinguishes them.',
             '- `data/candidates.csv`: 3,500 complete, replayable policy variants with simulated labels.',
             '- `data/applied_changes.csv`: real installed source blocks and their hashes; no invented impact attached.',
             '- `data/source_file_index.csv`: exact old/new paths, hashes and clickable diff-page paths.',
             '- `sources/old/` and `sources/new/`: complete source snapshots, including the directly embedded algorithms.',
             '- `diffs/`: HTML side-by-side comparisons with links to complete old/new source.',
             '- `candidate_code/`: the shared old configuration and 3,500 complete candidate headers.',
             '- `patches/`: applied block patches, full-file patches and proposed candidate patches.',
             '- `statistics/`: mean, median, standard deviation, percentiles, modal intervals and candidate rankings.',
             '- `graphs/`: six standalone SVGs for slides.',
             '- `scripts/`: portable analysis and bundle-verification tools.', '',
             '## Where the integrated algorithms live', '']
    location = json.loads((HOME / 'embedded_kernels.json').read_text())
    for name, info in location.items():
        if not info.get('whole_file'):
            source = next(item for item in index if item['new_repo_path'] == info['source'])
            text.append(f'- {name}: [{info["source"]}]({source["new_file"]}) — find `BEGIN INTEGRATED KERNEL {name}`.')
    text += ['', 'The old `src/cts/src/learning/` implementation directory is removed. Only small common flag/configuration headers remain shared.',
             'The standalone checks extract exact kernel blocks from the production translation units before compiling; they do not test a separate implementation.',
             'Some embedded algorithms are tested extension kernels rather than active production call paths. The KD-tree, segment tree, Fenwick tree, budget DP, spatial ordering and interval lookup have call sites in the changed OpenROAD code.', '',
             '## Interpreting “best” and “most changes”', '',
             'The highest-scoring variant is highest only under the fictional study labels. No measured optimum is established.',
             'Change-concentration graphs count actual added/removed production-source lines. They do not attribute timing gains to files.',
             'All candidate labels target the same shared policy configuration; they cannot support per-file effectiveness estimates.',
             'No full OpenROAD build, physical-design flow or signoff evaluation was performed.', '',
             '## Rebuild the entire folder', '',
             'From `suite`, run `make learning-final`. From this folder, `make rebuild` uses the original checkout.',
             'Original source branch: `eda/learning_draft_final_evolved_code_openroad_v2`.', '']
    (FINAL / 'README.md').write_text('\n'.join(text) + '\n')
    (FINAL / 'Makefile').write_text('''SHELL := /bin/bash
PYTHON ?= python3
OPENROAD ?= ../external/OpenROAD
.DEFAULT_GOAL := stats
.PHONY: stats graphs report verify test rebuild serve
stats report:
	@$(PYTHON) scripts/study_stats.py --root .
graphs:
	@$(PYTHON) scripts/study_stats.py --root .
	@$(PYTHON) scripts/render_graphs.py --root .
verify:
	@$(PYTHON) scripts/verify_bundle.py
test:
	@$(MAKE) --no-print-directory -C $(OPENROAD)/learning_evolution test
rebuild:
	@$(PYTHON) $(OPENROAD)/learning_evolution/tools/build_final.py
serve:
	@$(PYTHON) -m http.server 8000 --bind 127.0.0.1
''')
    # Linked markdown inventory is useful in editors that cannot render HTML.
    lines = ['# Exact old/new source file index', '', 'Use Compare for a side-by-side view; Old and New open complete files.', '']
    for item in index:
        lines.append(f'- **{item["new_repo_path"]}**: [Old]({item["old_file"]}) · [New]({item["new_file"]}) · [Compare]({item["diff_page"]}) · [Patch]({item["full_patch"]}) (+{item["lines_added"]}/-{item["lines_removed"]})')
    (FINAL / 'SOURCE_INDEX.md').write_text('\n'.join(lines) + '\n')


def main():
    FINAL.mkdir(exist_ok=True)
    for directory in ['data', 'sources', 'diffs', 'candidate_code', 'patches/files', 'patches/candidates', 'patches/applied_blocks', 'scripts', 'statistics', 'graphs']:
        (FINAL / directory).mkdir(parents=True, exist_ok=True)
    # Retire only this generator's hash-named snapshots, preserving user files.
    for directory, pattern in [('diffs', '*.html'), ('patches/files', '*.patch'),
                               ('patches/applied_blocks', '*.patch'),
                               ('patches/candidates', '*.patch'), ('candidate_code', '*_new.h')]:
        for obsolete in (FINAL / directory).glob(pattern):
            if re.fullmatch(r'[0-9a-f]{20,64}(?:\.html|\.patch|_new\.h)', obsolete.name):
                obsolete.unlink()
    rows, applied, index = export_data()
    copy_file(HOME / 'tools/study_stats.py', Path('scripts/study_stats.py'))
    copy_file(HOME / 'tools/verify_bundle.py', Path('scripts/verify_bundle.py'))
    copy_file(HOME / 'tools/render_graphs.py', Path('scripts/render_graphs.py'))
    copy_file(HOME / 'tools/test_dashboard.cjs', Path('scripts/test_dashboard.cjs'))
    copy_file(HOME / 'tools/render_dashboard.py', Path('scripts/render_dashboard.py'))
    analysis = analyze(FINAL)
    render(FINAL)
    import render_dashboard
    render_dashboard.refresh(FINAL, analysis, rows, index)
    documentation(analysis, index)
    # Source/data checksums remain stable when graphs and statistics regenerate.
    checksums = {}
    for directory in ['data', 'sources', 'candidate_code', 'patches', 'views']:
        for path in sorted((FINAL / directory).rglob('*')):
            if path.is_file():
                checksums[str(path.relative_to(FINAL))] = hashlib.sha256(path.read_bytes()).hexdigest()
    (FINAL / 'CHECKSUMS.json').write_text(json.dumps(checksums, indent=2) + '\n')
    print('Final folder:', FINAL)


if __name__ == '__main__':
    main()
