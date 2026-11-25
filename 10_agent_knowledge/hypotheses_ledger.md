# Hypotheses ledger

| iter | cluster | hypothesis (short) | verdict | score vs champion | note |
|---|---|---|---|---|---|
| 2 | setup_strategy | You've hit your 5-hour limit · resets 7:50am (Asia/Calcutta) | rejected | +0.00000 | score +0.00000 below required gain +0.00200 |
| 3 | sizing | Delay-gain driven multi-candidate gate sizing to eliminate critical-path slew degradation | rejected | +0.00000 | gates failed: //src/rsz/test:TestInsertBuffer=FAILED; //src/rsz/test:TestNestedJournal=FAILED; //src/rsz/test:TestPreChe |
| 4 | sizing | Isolate absolute delay-gain ranking with API-compatible single-candidate sizing | rejected | +0.00000 | gates failed: //src/rsz/test:TestResizer=FAILED; //src/rsz/test:cpp_tests=FAILED |
| 5 | sizing | Recover suppressed sizing moves with cost-ranked feasible replacement selection | rejected | +0.00000 | score +0.00000 below required gain +0.00200 |
| 6 | buffering | Enable shared-critical-data rebuffering beyond the blanket fanout cutoff | rejected | -0.00039 | score -0.00039 below required gain +0.00200 |
| 7 | buffering | Choose split-load partitions by branch slack budgets instead of half the sink count | rejected | -0.00156 | score -0.00156 below required gain +0.00200 |
| 8 | setup_strategy | Select LEGACY path repairs by journaled measured WNS/TNS gain | rejected | +0.00063 | nangate45/jpeg: candidate evaluation failed (timeout); score +0.00063 below required gain +0.00200; instrumentation miss |
| 9 | setup_strategy | Rank repair targets by slack-weighted count of violating endpoints sharing each driver (multi-endpoint path-sharing) instead of per-path loa | rejected | -0.00276 | score -0.00276 below required gain +0.00200 |
| 10 | sizing | Criticality-weighted (Lagrangian-style) cell selection that charges upstream and side-load delay by their violation weight | rejected | +0.00000 | score +0.00000 below required gain +0.00200 |
| 11 | buffering | TNS-aware van Ginneken: carry per-option total sink violation and choose the lowest-TNS tree among those within epsilon of the best worst-si | rejected | -0.00004 | score -0.00004 below required gain +0.00200; instrumentation missing: no RSZ_EVOLVE counter lines printed, cannot tell i |
| 12 | setup_strategy | TNS-weighted lexicographic acceptance (WNS guard band + design TNS gain) replacing endpoint-only slack acceptance in the LEGACY repair loop | rejected | -0.00493 | score -0.00493 below required gain +0.00200 |
| 13 | setup_strategy | Two-phase repair: unchanged stock LEGACY loop, then a bottleneck-driven TNS-recovery phase with a hard post-stock WNS floor | accepted | +0.00206 |  |
| 14 | sizing | Joint path-window sizing by dynamic programming as a compound move inside the post-stock TNS-recovery phase | rejected | -0.00038 | score -0.00038 below required gain +0.00200 |
| 15 | buffering | TNS-weighted critical-sink isolation with measured cut-point search on shared bottleneck nets, inside the post-stock recovery phase | rejected | -0.00064 | score -0.00064 below required gain +0.00200 |
| 16 | setup_strategy | Lagrangian endpoint pricing with best-of-k measured moves and a ratcheting WNS floor in the post-stock TNS-recovery phase | rejected | -0.00014 | score -0.00014 below required gain +0.00200 |
| 17 | buffering | Required-time-ordered (LT-tree) fanout tree synthesis for shared high-fanout drivers as a measured move in the post-stock recovery phase | rejected | +0.00000 | score +0.00000 below required gain +0.00200 |
| 18 | buffering | Measured best-of-k criticality-partitioned gate cloning (critical-sink replica + stock van Ginneken on tolerant sinks) for shared high-fanou | rejected | -0.00024 | score -0.00024 below required gain +0.00200 |
| 19 | setup_strategy | Measured depth-2 beam search over coupled sizing sequences on data-path-only bottleneck stages, with ratcheting WNS floor and per-endpoint g | rejected | -0.00145 | score -0.00145 below required gain +0.00200 |
