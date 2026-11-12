"""Phase 1a: run Graphify (offline, code-only AST extraction) on OpenROAD and on an rsz-focused corpus.

08_graphify/full_openroad/graphify-out/{graph.json,GRAPH_REPORT.md,graph.html}
08_graphify/rsz_focus/graphify-out/...   (rsz + dbSta + sta headers + rsz tests + ORFS resize/cts Tcl)
plus GOD_NODES.txt and a callflow html for the rsz corpus."""
from __future__ import annotations

import os
import shutil
from pathlib import Path

from ..config import PATHS, Knobs
from ..util import log, run, write_text


def _graphify(knobs: Knobs) -> str:
    return shutil.which(knobs.graphify_bin) or os.path.expanduser("~/.local/bin/graphify")


def _corpus_rsz(dst: Path) -> None:
    """Assemble the rsz-focused corpus by copying (small) so graphify sees one tree."""
    if dst.exists():
        shutil.rmtree(dst)
    dst.mkdir(parents=True)
    src = PATHS.openroad_src / "src"
    pairs = [(src / "rsz", "rsz"), (src / "dbSta" / "include", "dbSta_include"), (src / "dbSta" / "src", "dbSta_src"),
             (src / "sta" / "include" / "sta", "sta_include"), (src / "sta" / "search", "sta_search"),
             (src / "sta" / "graph", "sta_graph"), (src / "sta" / "dcalc", "sta_dcalc"),
             (src / "est", "est"), (src / "dpl" / "include", "dpl_include")]
    for s, name in pairs:
        if s.exists():
            shutil.copytree(s, dst / name, ignore=shutil.ignore_patterns("*.ok", "*.def", "*.lef", "*.lib", "*.v", "*.odb", "*.gz", "*.png"))
    orfs = PATHS.orfs_src / "flow" / "scripts"
    (dst / "orfs_scripts").mkdir()
    for f in ("resize.tcl", "cts.tcl", "global_route.tcl", "util.tcl", "load.tcl", "detail_place.tcl", "floorplan.tcl", "global_place.tcl"):
        if (orfs / f).exists():
            shutil.copy2(orfs / f, dst / "orfs_scripts" / f)


def run_graphify(scope: str = "all", knobs: Knobs | None = None) -> int:
    knobs = knobs or Knobs.load()
    g = _graphify(knobs)
    if not shutil.which(g) and not Path(g).exists():
        log("graphify not found; pipx install graphifyy"); return 2
    rc = 0
    if scope in ("all", "rsz"):
        out = PATHS.graphify / "rsz_focus"
        corpus = out / "corpus"
        _corpus_rsz(corpus)
        log(f"graphify: extracting rsz-focused corpus ({sum(1 for _ in corpus.rglob('*') if _.is_file())} files)")
        r = run([g, "extract", corpus, "--code-only", "--out", out, "--max-workers", "8"], timeout=7200, log_file=out / "extract.log")
        rc |= 0 if r.ok else 1
        gj = out / "graphify-out" / "graph.json"
        if gj.exists():
            # communities + GRAPH_REPORT.md + graph.html (offline: keep placeholder community names)
            run([g, "cluster-only", out, "--no-label"], timeout=3600, log_file=out / "cluster.log")
            gn = run([g, "god-nodes", "--graph", gj, "--top", "40"], timeout=600)
            write_text(out / "GOD_NODES.txt", gn.stdout)
            run([g, "export", "callflow-html", "--graph", gj, "--output", out / "callflow.html"], timeout=1200)
            run([g, "tree", "--graph", gj, "--output", out / "GRAPH_TREE.html", "--root", corpus], timeout=1200)
            log(f"graphify: rsz_focus done -> {gj}")
    if scope in ("all", "full"):
        out = PATHS.graphify / "full_openroad"
        out.mkdir(parents=True, exist_ok=True)
        log("graphify: extracting full OpenROAD src (this is big; ~10-30 min)")
        r = run([g, "extract", PATHS.openroad_src / "src", "--code-only", "--out", out, "--max-workers", "8", "--no-gitignore"],
                timeout=14400, log_file=out / "extract.log")
        rc |= 0 if r.ok else 1
        gj = out / "graphify-out" / "graph.json"
        if gj.exists():
            run([g, "cluster-only", out, "--no-label", "--no-viz"], timeout=7200, log_file=out / "cluster.log")
            gn = run([g, "god-nodes", "--graph", gj, "--top", "60"], timeout=600)
            write_text(out / "GOD_NODES.txt", gn.stdout)
            log(f"graphify: full_openroad done -> {gj}")
    return rc
