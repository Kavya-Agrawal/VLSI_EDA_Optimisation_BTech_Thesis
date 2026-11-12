"""`make viz`: PNG plots + a self-contained index.html under 07_visualizations/.

Plots: WNS/TNS per design across iterations (baseline line, champion staircase, every candidate as a dot
coloured by cluster), accept/reject timeline, cost per iteration, worst-path slack histogram before/after for
the champion. Pure matplotlib; no network."""
from __future__ import annotations

import html
from pathlib import Path
from typing import Any

from ..budget import Budget
from ..config import PATHS, Knobs
from ..eval.baseline import load_baseline
from ..knowledge.ledger import champion_record, load_lineage
from ..util import log, read_json, write_text

COLORS = {"setup_strategy": "#1f77b4", "sizing": "#ff7f0e", "buffering": "#2ca02c", "hold": "#d62728", "drv": "#9467bd", "timing_model": "#8c564b"}


def render_all() -> None:
    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt

    PATHS.viz.mkdir(parents=True, exist_ok=True)
    knobs = Knobs.load()
    base = load_baseline().get("variants", {}).get(knobs.sdc_variant, {})
    lin = load_lineage()
    its = [i for i in lin.get("iterations", []) if i.get("per_design")]
    designs = sorted(k for k, a in base.items() if a.get("ok"))
    made: list[str] = []

    # 1. WNS and TNS per design over iterations
    for metric, key_c, key_r in (("WNS", "wns_cand", "wns_ref"), ("TNS", "tns_cand", "tns_ref")):
        if not designs:
            break
        fig, axes = plt.subplots(len(designs), 1, figsize=(9, 2.6 * len(designs)), squeeze=False)
        for ax, d in zip(axes[:, 0], designs):
            bval = base[d]["post"]["wns_setup" if metric == "WNS" else "tns_setup"]["mean"]
            ax.axhline(bval, color="grey", ls="--", lw=1, label="baseline (stock)")
            champ_line, champ_val = [], bval
            for i in its:
                v = i["per_design"].get(d)
                if not v:
                    continue
                ax.scatter(i["iteration"], v[key_c], color=COLORS.get(i.get("cluster"), "black"), s=28, zorder=3,
                           marker="o" if i.get("accepted") else "x")
                if i.get("accepted"):
                    champ_val = v[key_c]
                champ_line.append((i["iteration"], champ_val))
            if champ_line:
                ax.step([x for x, _ in champ_line], [y for _, y in champ_line], where="post", color="black", lw=1.5, label="champion")
            ax.set_title(f"{d}: post-repair {metric} (ns), {knobs.sdc_variant} SDC"); ax.set_xlabel("iteration"); ax.grid(alpha=.3)
            ax.legend(loc="best", fontsize=8)
        fig.tight_layout(); p = PATHS.viz / f"{metric.lower()}_per_design.png"; fig.savefig(p, dpi=130); plt.close(fig); made.append(p.name)

    # 2. accept/reject timeline + cost
    all_its = lin.get("iterations", [])
    if all_its:
        per = Budget.load(PATHS.agent_data / "budget.json").per_iteration()
        fig, (a1, a2) = plt.subplots(2, 1, figsize=(9, 5), sharex=True)
        for i in all_its:
            c = COLORS.get(i.get("cluster"), "black")
            a1.bar(i["iteration"], float(i.get("score_vs_champion") or 0), color=c, alpha=.9 if i.get("accepted") else .4)
            a2.bar(i["iteration"], per.get(int(i["iteration"]), {}).get("usd", 0.0), color=c)
        a1.axhline(0, color="grey", lw=.8); a1.set_ylabel("score vs champion"); a1.grid(alpha=.3)
        a2.set_ylabel("USD"); a2.set_xlabel("iteration"); a2.grid(alpha=.3)
        from matplotlib.patches import Patch
        a1.legend(handles=[Patch(color=c, label=k) for k, c in COLORS.items()], fontsize=7, ncol=3)
        fig.tight_layout(); p = PATHS.viz / "iterations_score_cost.png"; fig.savefig(p, dpi=130); plt.close(fig); made.append(p.name)

    # 3. worst-path slack histogram: baseline vs champion
    champ = champion_record()
    if champ.get("results_dir") and designs:
        fig, axes = plt.subplots(1, len(designs), figsize=(4 * len(designs), 3), squeeze=False)
        for ax, d in zip(axes[0], designs):
            bdir = Path(base[d]["dirs"][0])
            bs = [float(p["slack"]) for p in (read_json(bdir / "paths_post.json", []) or [])]
            cdir = Path(champ["results_dir"]) / "runs" / d.replace("/", "__") / f"{knobs.sdc_variant}_r0"
            cs = [float(p["slack"]) for p in (read_json(cdir / "paths_post.json", []) or [])]
            if bs: ax.hist(bs, bins=15, alpha=.5, label="baseline")
            if cs: ax.hist(cs, bins=15, alpha=.5, label="champion")
            ax.set_title(f"{d}: worst-path slack (ns)"); ax.legend(fontsize=8)
        fig.tight_layout(); p = PATHS.viz / "worst_path_slack_hist.png"; fig.savefig(p, dpi=130); plt.close(fig); made.append(p.name)

    # 4. index.html
    rows = []
    for i in all_its:
        tag = i.get("tag", "")
        rows.append(f"<tr><td>{i.get('iteration')}</td><td>{html.escape(str(i.get('status', '')))}</td><td>{html.escape(str(i.get('cluster', '')))}</td>"
                    f"<td>{float(i.get('score_vs_champion') or 0):+.5f}</td><td>{html.escape(str(i.get('title') or i.get('error') or '')[:90])}</td>"
                    f"<td><a href='../06_evolved_results/{tag}/summary.md'>summary</a> · <a href='../06_evolved_results/{tag}/feedback.md'>feedback</a> · "
                    f"<a href='../02_openroad_evolved/candidates/{tag}/candidate.patch'>patch</a> · <a href='../02_openroad_evolved/candidates/{tag}/HYPOTHESIS.md'>hypothesis</a></td></tr>")
    page = f"""<!doctype html><meta charset='utf-8'><title>rsz evolution</title>
<style>body{{font-family:system-ui;margin:24px;max-width:1100px}}table{{border-collapse:collapse}}td,th{{border:1px solid #ccc;padding:4px 8px;font-size:13px}}img{{max-width:100%}}</style>
<h1>OpenROAD Resizer evolution — {html.escape(knobs.sdc_variant)} SDC</h1>
<p>champion: iteration {champ.get('iteration', 0)} · {html.escape(str(champ.get('hypothesis') or 'original rsz')[:200])}</p>
{''.join(f"<h2>{m}</h2><img src='{m}'>" for m in made)}
<h2>Iterations</h2><table><tr><th>#</th><th>status</th><th>cluster</th><th>score vs champion</th><th>title</th><th>links</th></tr>{''.join(rows)}</table>
<p><a href='../05_baseline_results/SUMMARY.md'>baseline summary</a> · <a href='../10_agent_knowledge/hypotheses_ledger.md'>hypotheses ledger</a> · <a href='../08_graphify/rsz_focus/graphify-out/graph.html'>knowledge graph</a></p>"""
    write_text(PATHS.viz / "index.html", page)
    log(f"viz: {PATHS.viz / 'index.html'} ({len(made)} plots)")
