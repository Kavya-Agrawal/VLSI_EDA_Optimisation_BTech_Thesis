# OpenROAD Code Evolution & Implementation Review

Open [index.html](index.html) for the review dashboard, source comparisons, formatted code viewers, and candidate browser.
Open [graphs.html](graphs.html) for empirical distribution plots and parameter analysis figures.

## Commands from this folder

```sh
make stats     # Compute descriptive summary statistics across candidate variants
make graphs    # Regenerate standalone SVG figures and statistical analysis
make verify    # Verify SHA-256 checksums, candidate integrity, and HTML links
make test      # Run integrated-source kernel regression checks
```

## Candidate Policy Evaluation Summary

- wns_impact_pct: mean 1.1507%, median 0.7177%, P1 0.0128%, P99 4.8831%.
- tns_impact_pct: mean 1.1499%, median 0.6999%, P1 0.0181%, P99 4.8793%.
- combined_timing_impact_pct: mean 1.1503%, median 0.6257%, P1 0.0770%, P99 4.7518%.

Percentiles interpolate at `(n - 1) * p / 100`. Standard deviation is the sample statistic.
Mode is reported as the most populated fixed-width interval (0.25 percentage points for timing metrics).

## What each directory contains

- `data/all_code_changes.csv`: combined applied blocks and proposed variants.
- `data/candidates.csv`: 3,500 complete, replayable policy configuration headers.
- `data/applied_changes.csv`: installed source blocks, line numbers, and cryptographic hashes.
- `data/source_file_index.csv`: exact old/new paths, hashes, and clickable diff-page paths.
- `sources/old/` and `sources/new/`: complete source snapshots of original and evolved code.
- `views/sources/`: formatted in-browser HTML code viewers with line numbers.
- `diffs/`: HTML side-by-side colorized comparisons with links to full source code.
- `candidate_code/`: base configuration and 3,500 candidate headers.
- `patches/`: applied block patches, full-file patches, and candidate patches.
- `statistics/`: mean, median, standard deviation, percentiles, modal intervals, and rankings.
- `graphs/`: standalone SVG figures for documentation and slides.
- `scripts/`: analysis, site generation, and bundle-verification tools.

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

## Rebuild the entire folder

From `suite`, run `make learning-final`. From this folder, `make rebuild` uses the original checkout.
Original source branch: `eda/learning_draft_final_evolved_code_openroad_v2`.

