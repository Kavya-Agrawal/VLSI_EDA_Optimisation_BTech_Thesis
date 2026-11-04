# OpenROAD evolution: final review folder

Open [index.html](index.html) for the offline dashboard, graphs, source comparisons and candidate browser.

**Provenance:** code edits are real; candidate impact labels are simulated. Averages describe this CSV, not an expected real-world tool improvement.

## Commands from this folder

```sh
make stats
make graphs
make report
make verify
make test
```

`make stats`, `graphs`, `report` and `verify` need only Python 3 and the bundled files.
`make test` requires the original OpenROAD checkout and a C++20 compiler.

## CSV-derived summary

- simulated_wns_impact_pct: mean 1.1507%, median 0.7177%, P1 0.0128%, P99 4.8831%.
- simulated_tns_impact_pct: mean 1.1499%, median 0.6999%, P1 0.0181%, P99 4.8793%.
- combined_timing_label_pct: mean 1.1503%, median 0.6257%, P1 0.0770%, P99 4.7518%.

The all-candidate arithmetic mean is the primary summary; filtering accepted/high-scoring rows would bias it upward.
Percentiles interpolate at `(n - 1) * p / 100`. Standard deviation is the sample statistic.
Mode is reported as the most populated fixed-width interval (0.25 percentage points for timing labels), not an unstable exact floating-point mode.

## What each directory contains

- `data/all_code_changes.csv`: combined applied blocks and proposed variants; record_kind distinguishes them.
- `data/candidates.csv`: 3,500 complete, replayable policy variants with simulated labels.
- `data/applied_changes.csv`: real installed source blocks and their hashes; no invented impact attached.
- `data/source_file_index.csv`: exact old/new paths, hashes and clickable diff-page paths.
- `sources/old/` and `sources/new/`: complete source snapshots, including the directly embedded algorithms.
- `diffs/`: HTML side-by-side comparisons with links to complete old/new source.
- `candidate_code/`: the shared old configuration and 3,500 complete candidate headers.
- `patches/`: applied block patches, full-file patches and proposed candidate patches.
- `statistics/`: mean, median, standard deviation, percentiles, modal intervals and candidate rankings.
- `graphs/`: six standalone SVGs for slides.
- `scripts/`: portable analysis and bundle-verification tools.

## Where the integrated algorithms live

- Geometry: [src/cts/src/SinkClustering_new.cpp](sources/new/src/cts/src/SinkClustering_new.cpp) — find `BEGIN INTEGRATED KERNEL Geometry`.
- KdTree: [src/cts/src/SinkClustering_new.cpp](sources/new/src/cts/src/SinkClustering_new.cpp) — find `BEGIN INTEGRATED KERNEL KdTree`.
- DisjointSet: [src/cts/src/SinkClustering_new.cpp](sources/new/src/cts/src/SinkClustering_new.cpp) — find `BEGIN INTEGRATED KERNEL DisjointSet`.
- SpanningTree: [src/cts/src/SinkClustering_new.cpp](sources/new/src/cts/src/SinkClustering_new.cpp) — find `BEGIN INTEGRATED KERNEL SpanningTree`.
- LocalSearch: [src/cts/src/SinkClustering_new.cpp](sources/new/src/cts/src/SinkClustering_new.cpp) — find `BEGIN INTEGRATED KERNEL LocalSearch`.
- SpatialOrder: [src/cts/src/SinkClustering_new.cpp](sources/new/src/cts/src/SinkClustering_new.cpp) — find `BEGIN INTEGRATED KERNEL SpatialOrder`.
- Fenwick: [src/rsz/src/policy/SetupLegacyBase_new.cc](sources/new/src/rsz/src/policy/SetupLegacyBase_new.cc) — find `BEGIN INTEGRATED KERNEL Fenwick`.
- SlackTree: [src/rsz/src/policy/SetupLegacyBase_new.cc](sources/new/src/rsz/src/policy/SetupLegacyBase_new.cc) — find `BEGIN INTEGRATED KERNEL SlackTree`.
- BudgetDp: [src/rsz/src/policy/SetupLegacyBase_new.cc](sources/new/src/rsz/src/policy/SetupLegacyBase_new.cc) — find `BEGIN INTEGRATED KERNEL BudgetDp`.
- RepairOrder: [src/rsz/src/policy/SetupLegacyBase_new.cc](sources/new/src/rsz/src/policy/SetupLegacyBase_new.cc) — find `BEGIN INTEGRATED KERNEL RepairOrder`.
- IntervalIndex: [src/cts/src/TreeBuilder_new.cpp](sources/new/src/cts/src/TreeBuilder_new.cpp) — find `BEGIN INTEGRATED KERNEL IntervalIndex`.
- PartitionDp: [src/cts/src/HTreeBuilder_new.cpp](sources/new/src/cts/src/HTreeBuilder_new.cpp) — find `BEGIN INTEGRATED KERNEL PartitionDp`.
- TimingDag: [src/cts/src/LatencyBalancer_new.cpp](sources/new/src/cts/src/LatencyBalancer_new.cpp) — find `BEGIN INTEGRATED KERNEL TimingDag`.
- Pareto: [src/cts/src/TechChar_new.cpp](sources/new/src/cts/src/TechChar_new.cpp) — find `BEGIN INTEGRATED KERNEL Pareto`.
- MinCostFlow: [src/cts/src/TechChar_new.cpp](sources/new/src/cts/src/TechChar_new.cpp) — find `BEGIN INTEGRATED KERNEL MinCostFlow`.
- LazyQueue: [src/rsz/src/RecoverPower_new.cc](sources/new/src/rsz/src/RecoverPower_new.cc) — find `BEGIN INTEGRATED KERNEL LazyQueue`.
- RollbackSet: [src/rsz/src/RecoverPower_new.cc](sources/new/src/rsz/src/RecoverPower_new.cc) — find `BEGIN INTEGRATED KERNEL RollbackSet`.

The old `src/cts/src/learning/` implementation directory is removed. Only small common flag/configuration headers remain shared.
The standalone checks extract exact kernel blocks from the production translation units before compiling; they do not test a separate implementation.
Some embedded algorithms are tested extension kernels rather than active production call paths. The KD-tree, segment tree, Fenwick tree, budget DP, spatial ordering and interval lookup have call sites in the changed OpenROAD code.

## Interpreting “best” and “most changes”

The highest-scoring variant is highest only under the fictional study labels. No measured optimum is established.
Change-concentration graphs count actual added/removed production-source lines. They do not attribute timing gains to files.
All candidate labels target the same shared policy configuration; they cannot support per-file effectiveness estimates.
No full OpenROAD build, physical-design flow or signoff evaluation was performed.

## Rebuild the entire folder

From `suite`, run `make learning-final`. From this folder, `make rebuild` uses the original checkout.
Original source branch: `eda/learning_draft_final_evolved_code_openroad_v2`.

