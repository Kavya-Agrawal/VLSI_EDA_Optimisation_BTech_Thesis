# ConcreteSwapArithModules.hh

## Purpose
Declares `rsz::ConcreteSwapArithModules`, the only implementation of the abstract `SwapArithModules` interface (`src/SwapArithModules.hh`). It implements the `replace_arith_modules` step. The step finds hierarchical module instances (`dbModInst`) that implement arithmetic operators on the worst setup paths. It then swaps each one to a faster architecture by retargeting it to a sibling module of a different name. The `.hh` holds the declarations only. All logic is in `src/ConcreteSwapArithModules.cc`.

## Public entry points
All are `override`s of pure virtuals in `SwapArithModules`.

- `explicit ConcreteSwapArithModules(Resizer*)`: stores `resizer_`. It is constructed in the `Resizer` ctor initializer list as `std::make_unique<ConcreteSwapArithModules>(this)` (`Resizer.cc:207`). `Resizer` is a friend (`Resizer.hh:1220-1221`), so this class reads `resizer_->logger_`, `sta_` and `db_network_` directly.
- `bool replaceArithModules(int path_count, const std::string& target, float slack_threshold)`: the top-level driver. It calls `findCriticalInstances`, then `doSwapInstances`. It returns false if no critical instance is found or nothing was swapped. Its only caller is `Resizer::swapArithModules` (`Resizer.cc:5611`), which is reached from the Tcl command via `swap_arith_modules_cmd` (`Resizer.tcl:1128`, `Resizer.i:694`).
- `void findCriticalInstances(int path_count, const std::string& target, float slack_threshold, PtrSet<dbModInst>& insts)`: collects the arithmetic module instances on the worst paths. It is called by `replaceArithModules`.
- `void collectArithInstsOnPath(const sta::Path*, PtrSet<dbModInst>&)`: walks one path and adds every arithmetic `dbModInst` it passes through. It is called by `findCriticalInstances`.
- `bool isArithInstance(const sta::Instance*, dbModInst*& mod_inst)`: climbs the hierarchy upward from a leaf instance and returns the nearest ancestor that is an arithmetic module. Callers are `collectArithInstsOnPath` and `Resizer::findArithBoundaryPin` (`Resizer.cc:4119`). The latter uses it so that tie cells are not inserted inside an arithmetic module.
- `bool hasArithOperatorProperty(const dbModInst*)`: decides whether a mod inst is arithmetic. It is called by `isArithInstance`.
- `bool doSwapInstances(PtrSet<dbModInst>& insts, const std::string& target)`: performs the swaps. It is called by `replaceArithModules`.

Protected members: `init()` (lazy init), `produceNewModuleName(old, new&, target)`, and `bool init_ = false`. Note that this `init_` is a distinct, unrelated member from the base-class pointers; there is no name clash with the base.

## Inputs and outputs, precisely
**Reads**
- STA timing: `sta_->updateTiming(false)`, `sta_->endpoints()`, `sta_->slack(vertex, max_)`, `sta_->vertexWorstSlackPath(vertex, max_)`, and `PathExpanded` over the resulting path. Only the setup (`max_`) side is used.
- odb hierarchy: `dbInst`/`dbModInst` mapped through `db_network_->staToDb`, `dbModInst::getMaster()`, `dbModule::getOwner()`, `dbBlock::findModule(name)`, and `dbStringProperty::find(mod_inst, "implements_operator")`.
- Options: `path_count`, `slack_threshold` (a float, compared directly against the STA `Slack`), and `target` (a string; only `"setup"` is supported).
- Parasitics: not read here.

**Mutates / returns**
- `doSwapInstances` calls `dbModInst::swapMaster(new_master)` for each qualifying instance. This is the only netlist mutation. On return, `insts` is cleared and refilled with the *new* `dbModInst*` values returned by `swapMaster`.
- It logs via `logger_` and emits the metric `design__instance__count__swapped_arithmetic_operator`.
- Returns true if at least one swap happened.
- `findCriticalInstances` only fills the output set.
- `isArithInstance` writes `mod_inst`. It is set to nullptr at entry, after the `inst==nullptr` early return, so on a null input the out-param is left untouched.

**Info/warn/error IDs:** RSZ 151–154 are info, 155 is error, 157–159 and 161 are warn, and 160 is info.

## Algorithm / control flow
**`replaceArithModules`**
1. `init()`.
2. Log 151.
3. `findCriticalInstances`. If the set is empty, return false.
4. Return `doSwapInstances`.

**`findCriticalInstances`**
1. `sta_->updateTiming(false)` (an incremental update). The comment explains this is to avoid the endpoint set being modified mid-iteration.
2. Iterate all `sta_->endpoints()`. Keep every endpoint whose `slack(max_) < slack_threshold`.
3. `std::ranges::stable_sort` ascending by slack, so the worst endpoint comes first. Ties keep endpoint-set order.
4. Take the first `path_count` endpoints. For each one, take `vertexWorstSlackPath(max_)` and call `collectArithInstsOnPath`.
5. The set is deduplicated by `PtrSet`.
6. Log 152, 153 and 154. If `debugCheck(RSZ, "replace_arith", 1)`, it also lists the instances.

**`collectArithInstsOnPath`**
1. Build a `PathExpanded`. Do nothing unless `expanded.size() > 1`.
2. For `i` from `startIndex()` to `size()-1`, take the path's vertex and pin.
3. Only output pins (`direction->isAnyOutput()`) are considered. Take `network_->instance(pin)` and call `isArithInstance`. If it matches, insert the `dbModInst`.

**`isArithInstance`**
1. Start at the given instance. Loop: `staToDb(curr, db_inst, curr_mod_inst)`. If `curr_mod_inst` is non-null and `hasArithOperatorProperty` is true, return it.
2. Otherwise go to `network_->parent(curr)` and increment the depth.
3. Stop when the parent is null or the depth reaches `MAX_HIER_DEPTH = 100`. At 100 it emits warn 161 and returns false.

**`hasArithOperatorProperty`**
- True if the mod inst has the string property `implements_operator`.
- Otherwise true if the master module name starts with `ALU_` or `MACC_` (`strncmp`).

**`produceNewModuleName`** (target `"setup"` only)
- The default is `new_name = old_name`.
- Name starts with `ALU_`: the first of `HAN_CARLSON`, `BRENT_KUNG`, `SKLANSKY` found in the name (searched in that order) is cut at its position. `KOGGE_STONE` is appended, so any suffix after the architecture token is discarded.
- Name starts with `MACC_`: if it contains `BOOTH`, the name is cut there and `BASE` is appended.
- Any other target calls `logger_->error(RSZ, 155, ...)`, which is fatal.

**`doSwapInstances`**
1. For each `dbModInst`, get `old_master`. If it is null, warn 157 and skip.
2. Compute `new_name`. If it equals `old_name`, skip.
3. Get the owner block. If it is null, warn 158 and skip.
4. `block->findModule(new_name)`. If it is null, warn 159 and skip.
5. `inst->swapMaster(new_master)`. On a non-null return, count it and add it to `swappedInsts`.
6. Replace `insts` with `swappedInsts`. Log 160 and emit the metric.

**Caller-side follow-up** (`Resizer::swapArithModules`, `Resizer.cc:5599`): it runs `resizePreamble`, then opens an `IncrementalParasiticsGuard`. If a swap happened, it runs `ensureLevelized`, `updateParasitics`, `clearLogicConstants`, `updateTiming(true)` and `findRequireds`.

## Key data structures
- `odb::PtrSet<odb::dbModInst>`: the odb pointer set used for the candidate and swapped sets.
- `std::vector<std::pair<Vertex*, Slack>>`: the violating endpoints. It is local to `findCriticalInstances`.
- `sta::PathExpanded`: the expanded path.
- Inherited from `SwapArithModules` and `sta::dbStaState`: `resizer_`, `db_network_`, `logger_`, `min_`, `max_` (set from `MinMax::min()` / `MinMax::max()`), and `sta_` / `network_` via `dbStaState::init`.
- The header's own state is `bool init_`. The `.cc` `init()` sets `logger_`, calls `dbStaState::init(resizer_->sta_)`, sets `db_network_`, and then sets `init_ = true`.

## Callers and callees (verified by reading)
- **Callers:** `Resizer::swapArithModules`, which is reached from Tcl `replace_arith_modules` via `swap_arith_modules_cmd` (`Resizer.tcl:1128`). `Resizer::findArithBoundaryPin` calls `isArithInstance`.
- **Callees:** STA (`Sta::updateTiming`, `endpoints`, `slack`, `vertexWorstSlackPath`, `PathExpanded`), `dbNetwork::staToDb`, odb (`swapMaster`, `findModule`, `getMaster`, `getOwner`, `dbStringProperty::find`), and `utl::Logger`.
- **Not called here:** the Resizer's own repair and sizing code, `Resizer::journal`/`undo`, and parasitics updates. Those are done by the caller.

## Invariants and "do not break"
- **Timing must be current before endpoint iteration.** Keep `updateTiming(false)` ahead of `sta_->endpoints()`.
- **The old `dbModInst*` is invalid after `swapMaster`.** Use the pointers returned in `insts`.
- **Full timing recomputation after a swap is mandatory.** The caller does `clearLogicConstants()` and `updateTiming(true)` because incremental update is incomplete after a module swap. Do not skip that step if you call `replaceArithModules` or `doSwapInstances` elsewhere.
- **Parasitics.** The caller's guard and `updateParasitics()` require correct levelization, so call `ensureLevelized()` first.
- **No journaling.** The swap is not journaled, so there is no rollback. Resizer's `journalBegin`/`journalRestore` is not involved here.
- **Determinism.** The sort is stable, but the ordering inside `PtrSet` depends on odb ID/pointer ordering. Swap order does not change the result, since each swap is independent.
- **`init()` is lazy.** `isArithInstance` is called from `Resizer::findArithBoundaryPin`, possibly before any replace call, so it calls `init()` itself. Keep that.
- **`dont_touch` is not checked.** See the weak spots below.
- **Hierarchy only.** The swap works on hierarchical `dbModInst`s. A flat netlist has no mod insts, so it is a no-op.

## Weak spots / assumptions an algorithm designer should know
- **Name-pattern driven.** Replacements exist only if modules named like `ALU_<...>_HAN_CARLSON/BRENT_KUNG/SKLANSKY...` and `MACC_<...>BOOTH...` have a pre-existing `KOGGE_STONE` or `BASE` sibling in the same block (typically generated by a Yosys/synth flow). If the sibling is missing, there is only warn 159 and the instance is skipped.
- **Only one direction and one target.** The only supported move is to Kogge-Stone for ALUs and BASE for multipliers, i.e. the fastest and largest. There is no area or power target, and no evaluation of the result. A swap can worsen area, power or congestion, and nothing reverts it if timing does not improve.
- **Any other `target` is a fatal `logger_->error`.** `"hold"` and `"area"` cannot be used.
- **Selection heuristic.** It uses endpoint slack compared to the threshold and the single worst path per endpoint, limited to the top `path_count` endpoints. Arithmetic modules on non-worst paths, or reached via near-critical reconvergent paths, are not seen.
- **Setup only.** Hold (`min_`) is never used. `min_` is unused.
- **`isArithInstance` returns the nearest arithmetic ancestor.** An arithmetic module nested inside another arithmetic module is swapped at the inner level only. The `implements_operator` property check ignores the property's value.
- **Name matching is a substring search.** `find` locates the first match and the suffix is dropped. A name that contains more than one token could be mis-edited.
- **`slack_threshold` units.** It is compared directly with STA slack in STA internal time units (seconds), against a float parameter.
- **Duplicate-looking declarations.** The header includes `<set>`, but `std::set` is unused here.
- **Swap cost.** The swap forces a full `updateTiming(true)`, which is expensive on large designs. Repeated invocation inside an optimization loop will be slow.
- **No `dont_touch` or legality checks.** No placement legality check is made and no `dont_touch` check is done on the mod inst. `swapMaster` changes the module contents, but placement of leaf cells inside is not re-legalized here.