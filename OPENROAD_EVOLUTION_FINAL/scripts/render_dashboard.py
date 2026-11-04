import html, json
from pathlib import Path
FINAL = Path(__file__).resolve().parents[1]
CSS = '\n:root{font-family:Arial,sans-serif;color:#162939;background:#f5f7f9}body{margin:0}\nmain{max-width:1200px;margin:auto;padding:32px}h1{font-size:30px;margin:8px 0 12px}\nh2{font-size:21px;margin-top:36px}p{line-height:1.55}a{color:#215e8c}\nnav{display:flex;gap:20px;flex-wrap:wrap;margin:24px 0;border-bottom:1px solid #ccd6df;padding-bottom:14px}\n.notice{padding:14px 18px;border-left:4px solid #b8753a;background:#faf4e9;line-height:1.5}\n.metrics{display:grid;grid-template-columns:repeat(4,minmax(0,1fr));gap:24px;margin:28px 0}\n.metric strong{display:block;font-size:30px;margin-top:8px}.muted{color:#526575;font-size:13px}\n.graphs{display:grid;grid-template-columns:repeat(2,minmax(0,1fr));gap:22px}\nfigure{margin:0;background:white;border:1px solid #dce3e9;padding:8px}figure img{width:100%;height:auto}\nfigcaption{padding:10px;font-size:13px;color:#526575}table{width:100%;border-collapse:collapse;background:white;font-size:13px}\nth,td{padding:11px 10px;border-bottom:1px solid #dce3e9;text-align:left;vertical-align:top}\nth{background:#eaf0f5;font-weight:600;position:sticky;top:0}code{font-size:12px;overflow-wrap:anywhere}\n.scroll{max-height:600px;overflow:auto;border:1px solid #dce3e9}input,select,button{font:inherit;padding:9px;border:1px solid #b9c6d0;background:white;border-radius:3px}\ninput{min-width:300px}button{cursor:pointer}.tools{display:flex;gap:12px;align-items:center;margin:12px 0;flex-wrap:wrap}\npre{white-space:pre-wrap;word-break:break-word;background:white;padding:20px;border:1px solid #dce3e9;line-height:1.45}\n.diff{font-family:monospace;font-size:12px;width:auto;min-width:100%}.diff td{padding:3px 6px;white-space:pre}.diff_header{background:#eef2f5}\n.diff_add{background:#dcecdf}.diff_sub{background:#f3deda}.diff_chg{background:#f2e8c7}\n@media(max-width:800px){main{padding:18px}.graphs,.metrics{grid-template-columns:1fr 1fr}input{min-width:180px}}\n'

def page(title, body):
    return '<!doctype html><html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>' + html.escape(title) + '</title><style>' + CSS + '</style></head><body>' + body + '</body></html>\n'

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

def refresh(root, analysis, rows, index):
    global FINAL
    FINAL = Path(root)
    dashboard(analysis, rows, index)
