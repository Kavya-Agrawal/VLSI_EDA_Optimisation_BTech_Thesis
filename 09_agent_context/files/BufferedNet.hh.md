# BufferedNet.hh

## Purpose
Declares `BufferedNet`, the immutable-ish binary-tree model of a buffered net. It is the shared representation used by Rebuffer, RepairDesign and Resizer to evaluate wire/buffer delay and capacitance. Leaves are sinks, internal nodes are Steiner junctions, and the root is the driver. The header also declares `FixedDelay`, a fixed-point femtosecond delay type, and `visitTree`, a recursive-lambda helper. Tree construction from Steiner/global-route data lives in `BufferedNet.cc`, as `Resizer::` members.

## Public entry points
- `enum class BufferedNetType {load, junction, wire, via, buffer}`.
- `BufferedNetPtr = std::shared_ptr<BufferedNet>`; `Requireds = std::array<sta::Required, RiseFall::index_count>`.
- **Five constructors**, one per type. The first argument `type` must match the constructor, otherwise `logger->critical` (RSZ 78/79/80/81/87).
  - load: `(type, loc, load_pin, corner, resizer)`
  - wire: `(type, loc, layer, ref, corner, resizer, estimate_parasitics)`
  - via: `(type, loc, layer, ref_layer, ref, corner, resizer)`
  - junction: `(type, loc, ref, ref2, resizer)`
  - buffer: `(type, loc, buffer_cell, ref, corner, resizer, estimate_parasitics)`
  - Callers: `Rebuffer.cc` (about 180 mentions), `RepairDesign.cc`, `Resizer.cc`, `BufferedNet.cc`, and `move/RebufferMt*`.
- Accessors: `type()`, `location()`, `cap()`, `fanout()`, `maxLoadSlew()`, `loadPin()`, `layer()`, `refLayer()`, `bufferCell()`, `ref()`, `ref2()`, `area()`, `corner()`, `metrics()`.
- Recursive queries: `length()`, `bufferCount()`, `loadCount()`, `maxLoadWireLength()`.
  - `maxLoadWireLength` is used by RepairDesign.cc:1235 and Resizer.cc:4442.
- RC helpers:
  - `wireRC(corner, resizer, est, res&, cap&)` per-meter R and C for a wire node. It is called from Rebuffer.cc, RepairDesign.cc:1508 and Resizer.cc:~8313.
  - `viaResistance(corner, resizer, est)` is called from Rebuffer.cc, RepairDesign.cc:1462 and Resizer.cc:~8294.
- Rebuffer annotations with setters/getters:
  - `slack`/`setSlack`, `delay`/`setDelay`, `arrivalDelay`/`setArrivalDelay`
  - `slackTransition`/`setSlackTransition`
  - `setCapacitance`, `setFanout`, `setMaxLoadSlew`
- `fitsEnvelope(Metrics target)` is used by Rebuffer.cc (about lines 1514, 1546, 1970-2089) for the "assured envelope" test.
- Debug: `to_string(resizer)`, `reportTree(...)`.
- `FixedDelay`: `toSeconds()`, comparison and arithmetic operators, `lerp`, and the constants `INF` (100 s) and `ZERO`.
- `visitor<F>` / `visitTree(f, args...)`. The lambda receives `(recurse, level, node...)`.
- `BufferedNet::null_layer = -1`.

Defined in `BufferedNet.cc` (not in the header):
- `Resizer::makeBufferedNet(drvr_pin, corner)` dispatches on `estimate_parasitics_->getParasiticsSrc()`:
  - `kPlacement` → `makeBufferedNetSteiner`
  - `kGlobalRouting` / `kDetailedRouting` → `makeBufferedNetGroute`
  - `kNone` → `nullptr`
- `Resizer::makeBufferedNetSteinerOverBnets(root, sinks, corner)`.
- `Resizer::stitchTrees(outer, stitching_load, inner)`.

## Inputs and outputs, precisely
- **Constructors** read:
  - Child nodes: cap, fanout, max_load_slew, area.
  - Resizer: `portCapacitance(port, corner)`, `portFanoutLoad`, `maxInputSlew`, `dbuToMeters`.
  - STA SDC: `corner->sdc()->portExtCap` for top-level-port loads, using the max over rise/fall.
  - Liberty: `buffer_cell->bufferPorts` and `area()`.
  - Parasitics: the wire constructor calls `wireRC`.
- **Constructor outputs** (fields set at construction):
  - load: `cap_` = port cap, `fanout_` = `portFanoutLoad`, `max_load_slew_` = `maxInputSlew`.
  - junction: `cap_` and `fanout_` are summed, `max_load_slew_` is the min of the children, `area_` is summed.
  - wire: `cap_ = ref.cap + dbuToMeters(length) * wire_cap`, and the rest is inherited from `ref`.
  - via: everything is inherited from `ref`.
  - buffer: `cap_`, `fanout_` and `max_load_slew_` are the buffer input pin's values, so they do not inherit from `ref`. `area_ = ref.area + cell area`.
- **`wireRC`**:
  - If `layer_ == null_layer`, it uses the direction-weighted blend `dx*H + dy*V` of `wireSignalH/VResistance/Capacitance(corner)`. `dx` and `dy` are the fractions of the segment length along each axis.
  - Otherwise it calls `estimate_parasitics->layerRC(routing layer)`.
  - It returns per-meter res and cap.
- **`viaResistance`**: sums `layerRC` of each cut layer from `min(layer, ref_layer)` to `max(layer, ref_layer)`. If that gives 0 it falls back to `cut_layer->getResistance()`. It raises an error (RSZ 93) if the cut layer is missing.
- **Builders** read:
  - `est->makeSteinerTree` (placement-based), or `global_router_->getPinGridPositions` and `getRoutes()` (global-routing-based).
  - `network->isLoad(pin)`, plus odb net lookup (`findFlatDbNet`).
- **Builder output**: a `BufferedNetPtr`, or `nullptr`.
- Nothing mutates odb, STA or parasitics.

## Algorithm / control flow
- **`FixedDelay`**:
  - The constructor does `value_fs_ = float * 1e15`, truncating to int64. It errors (RSZ 1008) if |value| > 100 s, but only when a non-null resizer is passed.
  - `INF` and `ZERO` are built with a null resizer.
  - `toSeconds` goes through `float`.
  - `lerp(a, b, t)` returns `b` exactly when `t == 1.0f`.
- **`makeBufferedNetSteiner`**:
  1. Build an `est::SteinerTree` for the driver pin. Return null if there is no driver point.
  2. Build bidirectional adjacency lists from `branch(i).n`.
  3. Run `makeBufferedNetFromTree`, a DFS from `drvrPt` with `from = kNullPt`.
  4. At each node, attach `load` leaves for pins that satisfy `network->isLoad`. A `pins_visited` set keyed by location means only the first Steiner node at a location contributes its pins.
  5. Combine multiple loads and child subtrees with left-leaning `junction` nodes.
  6. If `to_loc != from_loc` and the subtree is non-null, wrap it in a `wire` node placed at `from` and pointing to `to`. `layer = null_layer`.
  7. Delete the tree.
- **`makeBufferedNetSteinerOverBnets`**: the same as above, but the leaves are caller-supplied `BufferedNetPtr` sinks. They are grouped by location in a `std::map<Point, vector>`, and the tree comes from `makeSteinerTree(root, sink_points)`.
- **`makeBufferedNetGroute`**:
  1. Look up the odb net. If it is missing, error RSZ 106. If it has only 1 term, warn RSZ 104 and return null.
  2. Map grid points to pins, keyed by `(x, y, conn_layer)`. Locate the driver's route point.
  3. Build adjacency from `GSegment`s.
  4. DFS with a `visited` set. A loop returns `nullptr` for that branch ("Loop found in groute").
  5. A wire node is emitted when the xy position changes. When only the layer changes it emits a `via` node. Wire nodes carry `to.layer()`.
  6. Check `loadCount() == pin_grid_locs.size() - 1`. If not, it errors (RSZ 74).
  7. If the driver is not found, warn RSZ 73 and return null.
- **`stitchTrees`**:
  - It replaces the `load` node whose pin is `stitching_load` (typically a buffer input being removed) with `inner_tree`.
  - Unchanged subtrees are shared (pointer equality), not copied. Changed nodes are rebuilt through the constructors, so cap and area are recomputed.
  - If the layers are equal but the locations differ, it inserts a wire.
  - If the layers differ, it inserts a via stack plus a wire.
  - If either layer is below 1 (incomplete layer assignment), it returns `inner_tree` unchanged with no connecting wire.
- **`fitsEnvelope`**: `slack >= target.slack && cap <= target.cap && maxLoadSlew >= target.max_load_slew && fanout <= target.fanout`. The last three use `sta::fuzzyLessEqual` / `fuzzyGreaterEqual`.
- **`bufferCount`, `loadCount`, `maxLoadWireLength`**: plain recursion. `maxLoadWireLength` sums wire lengths down to the next buffer or load and takes the max over junction branches. It stops at `buffer`, which returns 0.

## Key data structures
- **`BufferedNet` fields**:
  - Structure: `type_`, `location_`, `load_pin_`, `buffer_cell_`, `layer_`, `ref_layer_`, `ref_`, `ref2_`, `corner_`.
  - Electrical: `cap_`, `fanout_` (float), `max_load_slew_` (init `sta::INF`).
  - Aggregate: `area_`, the sum of buffer area downstream.
  - Rebuffer annotations: `slack_transitions_`, `slack_`, `delay_`, `arrival_delay_`.
- **`Metrics`**: `{slack, cap, max_load_slew, fanout}` with `withSlack` and `withCap`. The last three fields are uninitialised by default.
- **`FixedDelay`**: int64 femtoseconds.
- **Meaning of `location_` by type**:
  - wire: the near/driver end. The wire runs from `location` to `ref->location`.
  - buffer: the buffer's driver (output) pin location. `ref` is the subtree it drives.
  - junction: the Steiner point.
- **Tree shape**: junctions have `ref` as the left child and `ref2` as the right child. `ref2_` is null for every other non-load type.

## Callers and callees (verified by reading)
- Callers are the Rebuffer, RepairDesign and Resizer files above, plus `move/RebufferMt*.cc`.
- Callees:
  - Resizer: `portCapacitance`, `portFanoutLoad`, `maxInputSlew`, `dbuToMeters`, `network()`, `logger()`, `db_` (private member, so `BufferedNet` must be a friend or the access is via `db_`).
  - `est::EstimateParasitics`: `wireSignal{H,V}{Resistance,Capacitance}`, `layerRC`, `makeSteinerTree`, `getParasiticsSrc`.
  - `grt::GlobalRouter`: `getPinGridPositions`, `getRoutes`.
  - `dbNetwork`: `findFlatDbNet`, `dbToSta`, `staToDb`.
  - `sta::Sdc::portExtCap`, and Liberty `bufferPorts`.

## Invariants and "do not break"
- **Cached aggregates**: `cap_`, `fanout_`, `max_load_slew_` and `area_` are computed once in the constructor.
  - There is no recomputation, so any mutation through `setCapacitance`, `setFanout` or `setMaxLoadSlew` must keep parents consistent. Parents are not updated.
  - Rebuild bottom-up through the constructors, as `stitchTrees` does.
- **Sharing**: subtrees are shared via `shared_ptr` across candidate options in Rebuffer's DP. Do not mutate a node in place after it has been shared. The annotation setters (`setSlack`, `setDelay` and so on) are the exception, so annotate only nodes you own.
- **Node/ref contract**: `ref()` must be non-null for wire, via, buffer and junction. `ref2()` is non-null only for junction.
- **Error paths**:
  - `wireRC` aborts via `critical` if called on a non-wire node, and `viaResistance` likewise on a non-via node.
  - `FixedDelay` errors above 100 s.
- **Determinism**: construction depends on `SteinerTree` branch order and on the ordering of `pins` and `adjacents`.
  - The `std::map<Point,…>` ordering is deterministic.
  - The sinks of the `makeBufferedNetSteinerOverBnets` path are ordered by input vector order.
- **dont_touch / journaling**: none here. The structure is read-only with respect to odb and STA.
  - Callers own journaling and rollback.
  - Dont_touch is also the caller's concern, since the builders do not filter it.
- **Parasitics**: `makeBufferedNet` returns null when `ParasiticsSrc` is `kNone`. The tree is a snapshot at the time of the call, and later placement changes do not update it.

## Weak spots / assumptions an algorithm designer should know
- **Buffer cap model**: the buffer node's `cap_` and `max_load_slew_` ignore `ref`, which is intended for upstream-visible values.
  - The downstream cap is stored only in the child.
  - `fitsEnvelope` therefore sees the buffer input, not the load behind it.
- **`FixedDelay` precision**:
  - Float truncation toward zero gives a resolution of 1 fs, but the `float` round trip limits `toSeconds()` precision (about 7 significant digits).
  - `operator*` is absent and `lerp` goes through float.
  - Values that are legitimate but above 100 s error out. `INF` is only 100 s.
- **`Metrics` fields** other than `slack` are uninitialised by default, so construct all four explicitly.
- **`wireRC` with `null_layer`** applies the average H/V layer RC. It ignores the actual layer and any non-Manhattan detail.
  - Placement-based trees (Steiner) therefore always use `null_layer`.
  - Only the global-route trees carry real layers and via nodes.
- **Steiner builder drops pins**: a Steiner node at a location already in `pins_visited` contributes no pins. This assumes the tree places all pins of a point on the first node visited.
  - Non-load pins (drivers, other outputs) are skipped by `isLoad`.
- **`makeBufferedNetGroute` strictness**: a loop in the route yields a null branch, which can cause the later `loadCount` mismatch error (RSZ 74). A route with fewer reachable pins aborts the flow rather than falling back.
- **`stitchTrees` with incomplete layers** (layer < 1) drops the wire and via between the removed buffer's input and output. This slightly misestimates RC.
  - The wire-connection code reads `node->layer()` of a load node, which is `null_layer` (−1) for a load node.
  - In practice, with Steiner (non-groute) trees, this means the "different layers" branch is not taken. Both layers are `null_layer` and a wire is added.
- **`reportTree`** takes `level` as the indent width, with no cap on depth. The recursion is unbounded, so very deep trees (long chains) could stack-overflow in `visitTree` and constructors-by-recursion such as `bufferCount`.
- **`fanout` semantics**: it is a float seeded from `portFanoutLoad`, which is not the sink count. Use `loadCount()` for the actual sink count.
- **Slack/delay annotations** are only meaningful after Rebuffer sets them. The defaults are `ZERO`, and `fitsEnvelope` on an unannotated tree compares 0 slack.