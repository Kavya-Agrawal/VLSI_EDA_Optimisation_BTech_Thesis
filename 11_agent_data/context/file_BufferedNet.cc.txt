# BufferedNet.cc

## Purpose
Implements the `BufferedNet` tree. This is an immutable, shared-pointer binary tree of one net's routing topology: loads at the leaves, junctions at Steiner points, wires, vias and buffers on the edges. The file also holds the `Resizer` methods that build a `BufferedNet` from a placement-based Steiner tree or from global-route segments, and the stitching of two trees. Rebuffering, repair_design and buffer removal consume these trees. Timing annotations (slack, delay, arrival) are stored in the nodes but filled in elsewhere (`Rebuffer.cc`).

## Public entry points
- `FixedDelay::FixedDelay(sta::Delay, Resizer*)`: converts float seconds to int64 femtoseconds (`second_ = 1e15`). If `resizer` is non-null and the value is outside ±100 s (`INF`), it raises error RSZ-1008. `FixedDelay::INF` is 100 s and `ZERO` is 0. The default constructor gives 0.
- Five `BufferedNet` constructors, one per type (each is a typed overload, and the `type` argument is only sanity-checked):
  - load `(type, loc, load_pin, corner, resizer)`
  - junction `(type, loc, ref, ref2, resizer)`
  - wire `(type, loc, layer, ref, corner, resizer, estimate_parasitics)`
  - via `(type, loc, layer, ref_layer, ref, corner, resizer)`
  - buffer `(type, loc, buffer_cell, ref, corner, resizer, estimate_parasitics)`
  - Callers: the builders in this file, `Rebuffer.cc` (buffer and wire nodes) and `Resizer::stitchTrees`.
- `Resizer::makeBufferedNet(drvr_pin, corner)`: dispatches on `estimate_parasitics_->getParasiticsSrc()`.
  - `kPlacement` calls `makeBufferedNetSteiner`.
  - `kGlobalRouting` and `kDetailedRouting` call `makeBufferedNetGroute`.
  - `kNone` returns nullptr.
  - Callers: `Rebuffer.cc:2376` and `:3627`, `RepairDesign.cc:1226`, `Resizer.cc:8142-8143`.
- `Resizer::makeBufferedNetSteiner(drvr_pin, corner)`: builds from `est::SteinerTree`. Callers: `RepairDesign.cc:1231` (fallback when `makeBufferedNet` returns null) and `Resizer.cc:4440`.
- `Resizer::makeBufferedNetGroute(drvr_pin, corner)`: builds from GRT routes.
- `Resizer::makeBufferedNetSteinerOverBnets(root, sinks, corner)`: builds a Steiner tree over existing sub-trees. Each sink is a `BufferedNetPtr` located at its own `location()`. Caller: `Rebuffer.cc:218`.
- `Resizer::stitchTrees(outer, stitching_load, inner)`: replaces the load leaf `stitching_load` in `outer` with `inner`. Caller: `Resizer.cc:8147`, in the buffer-removal path, which builds `tree1` for the driver and `tree2` for the buffer output.
- Tree utilities:
  - `bufferCount()` and `loadCount()`: recursive counts.
  - `maxLoadWireLength()`: used by `RepairDesign.cc:1235` and `Resizer.cc:4442`.
  - `length()`: Manhattan distance to `ref_`.
  - `wireRC()` and `viaResistance()`.
  - `fitsEnvelope(Metrics)`: used by `Rebuffer.cc` at about 1514, 1546, 1970, 2026, 2076 and 2089.
  - `reportTree()`, `to_string()`.
  - Setters for cap, fanout, max load slew, slack, slack transition, delay and arrival delay.

## Inputs and outputs, precisely
- **Reads, load node:**
  - Liberty: `resizer->portCapacitance(port, corner)`, `portFanoutLoad`, `maxInputSlew(port, corner)`.
  - For top-level ports with no liberty port: SDC `portExtCap` (max rise/fall pin cap).
- **Reads, wire node:** `estimate_parasitics->wireSignalH/VResistance` and `H/VCapacitance(corner)`, or `layerRC(layer, corner)` when the layer is known. It also reads `db_->getTech()`.
- **Reads, via node:** `layerRC` of the cut layer above each routing layer. If it returns 0, it falls back to `cut_layer->getResistance()`.
- **Reads, buffer node:** `buffer_cell->bufferPorts` and the input pin cap, fanout and max slew.
- **Reads, builders:**
  - `estimate_parasitics_->makeSteinerTree(...)` and `getParasiticsSrc()`.
  - `global_router_->getPinGridPositions(db_net)` and `getRoutes()`.
  - `db_network_->findFlatDbNet`, `dbToSta` and `staToDb`.
  - `network_->isLoad`.
- **Mutates:** nothing in odb, STA or the parasitics. The only mutation is allocating new `BufferedNet` nodes. Setters change the nodes only.
- **Returns:** `BufferedNetPtr`, or nullptr when there is no tree.
- **Side effects:** log messages and debug prints under the groups `make_buffered_net`, `groute_bnet`, `repair_net` and `buffer_removal`.
- **Computed per node at construction** (not timing):
  - `cap_` is downstream capacitance. For a wire it is `ref.cap + dbuToMeters(length) * wire_cap_per_m`. A junction sums its children. A buffer node resets it to the buffer input cap.
  - `fanout_` is a sum over junctions. A buffer resets it to the buffer input fanout load.
  - `max_load_slew_` is the min over junctions. A buffer resets it to the buffer's max input slew.
  - `area_` is the sum of buffer cell areas downstream.
- **Defaults:** `slack_`, `delay_`, `arrival_delay_` default to ZERO, and `slack_transitions_` to nullptr.

## Algorithm / control flow
1. **`makeBufferedNetSteiner`**:
   - Build the tree with `makeSteinerTree(drvr_pin)`. If it is null or `drvrPt() == kNullPt`, return null.
   - Build an undirected adjacency list from `branch(i).n`, adding an edge when `j != i`.
   - Call `makeBufferedNetFromTree(from=kNullPt, to=drvr_pt)` and `delete tree`.
2. **`makeBufferedNetFromTree`** (recursive, depth-first):
   - At `to`, if the location is not yet in `pins_visited`, mark it. Then for each pin at that node that satisfies `isLoad`, create a load leaf and chain it into a left-leaning junction.
   - Only the first Steiner node at a location gets the pins. Duplicate nodes at the same coordinate are skipped.
   - Recurse into every adjacent node except `from`, and merge each result with a junction at `tree->location(to)`.
   - If a subtree exists, `from` is not null and the locations differ, wrap it in a wire node located at `location(from)` with `null_layer`. A wire node's location is its upstream end.
   - A zero-length edge produces no wire.
   - A subtree with no loads returns null and is dropped.
   - The result is a binary tree, not a multi-way tree.
3. **`makeBufferedNetSteinerOverBnets`** and **`makeBufferedNetFromTree2`**:
   - The same walk, but the "pins" are pre-built sinks from `sink_map`, which is keyed by exact point. Sinks sharing a point are chained into junctions.
   - `makeSteinerTree(root, sink_points)` is used. There is no per-pin `isLoad` filter.
4. **`wireRC`**:
   - With `null_layer`, it uses the corner's average H/V signal RC weighted by the |dx|/length and |dy|/length fractions.
   - With a layer, it uses `layerRC` for that routing layer.
5. **`makeBufferedNetGroute`**:
   - Find the dbNet. Error RSZ-106 if it is missing. If the net has one terminal, warn RSZ-104 and return null.
   - Fetch the GRT pin grid locations and map each `RoutePt` (x, y, layer) to its pins. Record the driver's route point.
   - If the driver is not found, warn RSZ-73 and return null.
   - Build the undirected adjacency from the net's `GSegment`s.
   - Recurse with a `visited` set. A revisited point returns null ("Loop found in groute").
   - At each point, attach loads, junction them, and recurse into adjacent points except `from`.
   - The edge is a `wire` if the (x, y) differ and a `via` if only the layer differs. A wire carries `to.layer()`.
   - Afterwards, if `loadCount() != pin_grid_locs.size() - 1`, raise error RSZ-74.
6. **`stitchTrees`**:
   - Run `visitTree` over `outer`. Wire, via and junction nodes are rebuilt only when a child changed (pointer equality), otherwise the original node is reused.
   - At the load leaf equal to `stitching_load`, take `buffer_in_loc` and `buffer_in_layer` from the leaf and `buffer_out_loc` and `buffer_out_layer` from `inner_tree`.
     - Same location and layer: return `inner_tree`.
     - Same layer, different location: a wire from the input location to `inner_tree`.
     - Different layers: if either layer is below 1, return `inner_tree` bare. Otherwise build a via stack, one via per layer step, from the out layer to the in layer, then add a wire if the locations differ.
   - Unknown node types hit `critical` RSZ-130.
   - Buffer nodes are not handled by the visitor's switch (see weak spots).
7. **`fitsEnvelope(target)`**: `slack >= target.slack` AND `fuzzyLessEqual(cap, target.cap)` AND `fuzzyGreaterEqual(maxLoadSlew, target.max_load_slew)` AND `fuzzyLessEqual(fanout, target.fanout)`.

## Key data structures
- `BufferedNetType`: `load`, `junction`, `wire`, `via`, `buffer`.
- `BufferedNet` fields:
  - Structure: `type_`, `location_`, `ref_`, `ref2_`, `layer_`, `ref_layer_`, `load_pin_`, `buffer_cell_`, `corner_`.
  - Electrical: `cap_`, `fanout_`, `max_load_slew_`, `area_`.
  - Rebuffer annotations: `slack_`, `delay_`, `arrival_delay_`, `slack_transitions_`.
- `FixedDelay`: int64 femtoseconds, with arithmetic and comparison operators and `lerp`.
- `Metrics {slack, cap, max_load_slew, fanout}`.
- File-local types:
  - `SteinerPtAdjacents` is `vector<vector<SteinerPt>>`.
  - `SteinerPtPinVisited` is an `unordered_set<Point>`.
  - `GRoutePtAdjacents`, `RoutePtSet` and `RoutePtPinMap` are keyed on `RoutePt` (x, y, layer) through `RoutePtHash` and `RoutePtEqual`.
  - `route_pt_null` is (0,0,0), used as the "no parent" sentinel.
- `visitTree` and `visitor` (in the header): a recursive-lambda helper that tracks the level.

## Callers and callees (verified by reading)
- **Callers:**
  - `Rebuffer.cc` calls `makeBufferedNet`, `makeBufferedNetSteinerOverBnets` and `fitsEnvelope`, and constructs wire and buffer nodes.
  - `RepairDesign.cc` calls `makeBufferedNet`, falling back to `makeBufferedNetSteiner`, then `maxLoadWireLength`.
  - `Resizer.cc` calls `makeBufferedNetSteiner`, `makeBufferedNet` and `stitchTrees`.
  - `move/RebufferMtGenerator.cc` goes through `Rebuffer::makeBufferedNet`.
- **Callees:**
  - `Resizer` (`portCapacitance`, `portFanoutLoad`, `maxInputSlew`, `dbuToMeters`, `logger`, `network`, `sdcNetwork`, `units`, and the `db_` member).
  - `est::EstimateParasitics` (`getParasiticsSrc`, `makeSteinerTree`, wire RC accessors, `layerRC`).
  - `est::SteinerTree`.
  - `grt::GlobalRouter` (`getPinGridPositions`, `getRoutes`).
  - `sta`: Liberty, Sdc `portExtCap`, Units, `fuzzy*`, hash helpers.
  - `dbNetwork` and `odb` tech and net APIs.
- The graph's other "called by" entries (Sta.cc and so on) appear to be include or name-collision noise. I found no direct use in this file's call sites outside the files listed above.

## Invariants and "do not break"
- **Immutability:** nodes are shared between trees (stitching reuses unchanged subtrees, and `Rebuffer` shares nodes). Only the annotation setters mutate, so call them only on freshly created nodes.
- **No netlist or odb change, so no journaling.** Building a tree is a pure read. A tree is a snapshot: it is stale once the netlist, placement or parasitics change.
- **Parasitics validity:** `makeBufferedNet` assumes `estimate_parasitics_` is configured for the right source. The `kNone` case returns nullptr, and callers must handle it.
- **Wire location convention:** a wire node's `location` is its driver-side end, and `ref_->location()` is the far end. `length()` depends on this.
- **Determinism:**
  - Steiner traversal order follows adjacency insertion order from the STT branch array.
  - GRT uses `unordered_map` adjacency, but only the order within each vector affects tree shape. The order of `GRoutePtAdjacents` bucket iteration is never walked.
  - `sink_map` is an ordered `std::map` keyed on Point.
- **Load pin count:** the driver is excluded because only pins for which `isLoad` is true become leaves. The GRT builder checks `loadCount == pins - 1` and errors otherwise.
- **`dont_touch`, legality:** not checked here. The callers decide which nets to process.
- **`FixedDelay::INF` is ±100 s.** A conversion outside that range is a hard error only when a non-null `Resizer` is passed.

## Weak spots / assumptions an algorithm designer should know
- **Buffer nodes in `stitchTrees`:** its switch has no `buffer` case, so a buffer node reaches `default` and RSZ-130 critical. The result is that stitching works only on trees without buffers (wire, via, junction and load).
- **Load-side `layer()`:** `stitchTrees` reads `node->layer()` of the load leaf and of `inner_tree`. Load leaves from the Steiner builder have `layer = null_layer (-1)`, and an `inner_tree` root that is a load or junction also has -1 (`junction` sets `null_layer`). Two -1 layers take the same-layer wire path, so this works. A mix of -1 with a real layer hits the "incomplete" early return, which drops the connection wire and via: `inner_tree` is returned with no connecting wire.
- **Via stack layer direction:** the via nodes are created with `layer` from `buffer_out_layer` stepping toward `buffer_in_layer`, but the wire above them is created last, so cap and res use only the final wire layer.
- **Via capacitance:** none is modeled (`cap_` of a via equals the child's). Via resistance is computed on demand only.
- **Placement-mode wires:** with `null_layer`, the RC is an H/V average weighted by the segment direction, and the layer is not assigned.
- **Steiner `from`/`to` equality:** a zero-length edge adds no wire and no via. A subtree without loads is silently dropped, so dangling Steiner branches vanish.
- **GRT cycle handling:** a loop or revisited point returns null for that branch, which silently loses sinks. The error only fires afterwards through the load-count check (RSZ-74), and only for the `Groute` builder.
- **GRT guard:** a one-terminal net warns and returns nullptr, and callers must tolerate that.
- **Load cap on top-level ports:** the cap uses the max of `pin_cap` over rise/fall only. Wire cap and fanout from `portExtCap` are ignored, `max_load_slew_` stays at INF, and `fanout_` stays at its default of 1.
- **Hierarchy:** the GRT builder uses `findFlatDbNet`, and the Steiner builder relies on `network_->isLoad`. Hierarchical-net handling is thin.
- **Dead variable:** in the groute builder, `RoutePt` is hashed with `sta::hashIncr` and `size_t`, with no collision protection beyond equality. No issue in practice, but `route_pt_null` (0,0,0) could in principle collide with a real grid point at the origin.
- **Single corner:** each tree is built for one corner. Its caps and RC are not valid for any other scene.
- **Recursion depth:** all builders and visitors recurse once per tree edge, so a very long or high-fanout net can run deep. Junction chains are left-leaning, so depth grows with fanout.