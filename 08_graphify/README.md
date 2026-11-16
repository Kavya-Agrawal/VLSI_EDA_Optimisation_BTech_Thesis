# 08_graphify — Graphify knowledge graphs of OpenROAD

- `full_openroad/`: whole `external/OpenROAD/src` (big-picture module map).
- `rsz_focus/`: rsz + dbSta + sta headers + rsz tests + ORFS resize/cts Tcl, with wiki and call-flow HTML.

Each contains `graph.json`, `GRAPH_REPORT.md`, `graph.html`. Regenerate with `make graphify`.

For a human-readable explanation of RSZ, open `rsz_focus/mentor_explainer.html`. The raw Graphify graph is an
engineering navigation index; the mentor explainer deliberately reduces it to the optimization decision loop.
