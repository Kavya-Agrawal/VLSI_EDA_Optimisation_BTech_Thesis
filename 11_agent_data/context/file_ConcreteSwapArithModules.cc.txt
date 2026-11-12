# ConcreteSwapArithModules.cc

## Purpose
Implements the `replace_arith_modules` command (the `SwapArithModules` interface). It finds hierarchical arithmetic modules (`dbModInst`s with an `implements_operator` property, or masters named `ALU_*` / `MACC_*`) on the worst setup paths. It then swaps each one to a faster architecture variant by renaming its master module: ALU → `KOGGE_STONE`, MACC → `BASE` (no Booth). It also provides `isArithInstance`, which `Resizer::findArithBoundaryPin` uses to keep tie cells out of arithmetic modules. It does not touch leaf cells, sizing, buffering or placement.

## Public entry points
(The class is in the `rsz` namespace. `init()` and `produceNewModuleName()` are protected. Every other method is public and virtual.)

- `explicit ConcreteSwapArithModules(Resizer*)` (`:55`). It is constructed in the Resizer constructor (`Resizer.cc:207`, `std::make_unique`) and stored in `Resizer::swap_arith_modules_`.
- `bool replaceArithModules(int path_count, const std::string& target, float slack_threshold)` (`:72`).
  - Top-level driver. It calls `init()`, logs RSZ-151, then `findCriticalInstances` and `doSwapInstances`.
  - Returns false if no critical arithmetic instances were found, otherwise whether any swap happened.
  - Caller: `Resizer::swapArithModules` (`Resizer.cc:5599`). That is reached from the Tcl `replace_arith_modules` through `rsz::swap_arith_modules_cmd` (`Resizer.i:694`).
- `void findCriticalInstances(int path_count, const std::string& target, float slack_threshold, odb::PtrSet<dbModInst>& insts)` (`:96`). It selects the violating endpoints and collects the arithmetic mod-insts on their worst paths. The `target` argument is not used here.
- `void collectArithInstsOnPath(const sta::Path*, odb::PtrSet<dbModInst>&)` (`:158`). It adds every arithmetic ancestor of every output pin on one path.
- `bool isArithInstance(const sta::Instance* inst, dbModInst*& mod_inst)` (`:185`).
  - It walks from `inst` up through `network_->parent()`. It returns the nearest enclosing `dbModInst` that is arithmetic, in `mod_inst`.
  - Callers: `collectArithInstsOnPath` and `Resizer::findArithBoundaryPin` (`Resizer.cc:4119`, used by tie-cell insertion). In the second call the return value is ignored and only the out-param is checked.
- `bool hasArithOperatorProperty(const dbModInst*)` (`:228`). Predicate: the `implements_operator` string property exists, or the master name starts with `ALU_` or `MACC_`.
- `bool doSwapInstances(PtrSet<dbModInst>& insts, const std::string& target)` (`:256`). It swaps masters in place. On return, `insts` holds the new instances.
- `void init()` (`:60`), protected. Lazy, one-shot (`init_` flag). It sets `logger_`, `dbStaState::init(resizer_->sta_)` and `db_network_`.
- `void produceNewModuleName(old, new&, target)` (`:314`), protected. Pure name mapping.

## Inputs and outputs, precisely
**Reads**
- STA: `sta_->updateTiming(false)`, `sta_->endpoints()`, `sta_->slack(vertex, max_)` and `sta_->vertexWorstSlackPath(vertex, max_)`.
  - `max_` is `MinMax::max()`, so only setup is analysed.
  - `PathExpanded` is built per path.
- Netlist: `db_network_->staToDb(inst, dbInst*, dbModInst*)`, `network_->parent`, and the `dbModInst` / `dbModule` hierarchy.
  - It also reads the odb string property `implements_operator` and the master module name.
  - `dbBlock::findModule(name)` is used to look up the replacement master.
- The inputs are `path_count`, `target`, and `slack_threshold` (in seconds, already parsed by Tcl `parse_time_margin_arg`).

**Mutates**
- odb: `dbModInst::swapMaster(new_master)` per swapped instance. It does not touch parasitics, placement or STA invalidation itself.
- Logs: RSZ-151, 152, 153, 154, 160 as info, and RSZ-157, 158, 159, 161 as warn. RSZ-155 is an error. Also the metric `design__instance__count__swapped_arithmetic_operator`.

**Returns** a bool. For `replaceArithModules` and `doSwapInstances` it means at least one swap happened.

**Post-processing is in `Resizer::swapArithModules`, not here (`Resizer.cc:5599-5625`).**
1. `resizePreamble()`.
2. If parasitics come from global or detailed routing, `opendp_->initMacrosAndGrid()`.
3. An `est::IncrementalParasiticsGuard` wraps the call.
4. If anything was swapped:
   - `sta_->ensureLevelized()`
   - `estimate_parasitics_->updateParasitics()`
   - `sta_->clearLogicConstants()`
   - `sta_->updateTiming(true)` (full update)
   - `sta_->findRequireds()`

## Algorithm / control flow
**1. `replaceArithModules`**
- Run `findCriticalInstances`. If the set is empty, return false.
- Otherwise return `doSwapInstances`.

**2. `findCriticalInstances`**
- Call `sta_->updateTiming(false)` first, so the endpoint set is not modified during iteration.
- Iterate all `sta_->endpoints()` and keep those with `slack(end, max_) < slack_threshold`. The comparison is strict, so threshold 0.0 means negative slack only.
- `std::ranges::stable_sort` by slack ascending. Ties keep endpoint-set iteration order.
- Take the first `path_count` endpoints. The loop does not break after `path_count`; it just skips the rest. For each, call `vertexWorstSlackPath(end, max_)` and then `collectArithInstsOnPath`. Results are unioned into one `odb::PtrSet<dbModInst>`.
- Under the debug flag `replace_arith` at level 1, list the instances and master names.
- The Tcl default is `path_count = 1000`, `target = setup`, `slack_threshold = 0.0`. Allowed targets are `setup|hold|power|area`.

**3. `collectArithInstsOnPath`**
- Build a `PathExpanded`. Only act if `size() > 1`.
- For `i` from `startIndex()` to the end, take `path(i)->vertex()` and its pin. For pins that are `isAnyOutput()` (output or bidirect), call `isArithInstance(network_->instance(pin))` and insert the resulting `dbModInst`.
- Input pins are skipped, so a module is collected only if some output pin on the path has the module as an ancestor.
- Top-level ports have `network_->instance` equal to the top instance. The walk from there finds no mod inst.

**4. `isArithInstance`**
- Start at `inst` and loop. At each level call `staToDb` to get `dbModInst*`.
- If it is non-null and `hasArithOperatorProperty` is true, return it. This is the innermost arithmetic ancestor.
- Otherwise go to `network_->parent`. Stop on null parent or when depth reaches `MAX_HIER_DEPTH = 100`, where it warns RSZ-161.
- The warning check is `hier_depth >= 100` after the loop. It can also fire when a root is reached at exactly depth 100.
- `inst == nullptr` returns false.

**5. `hasArithOperatorProperty`**
- True if `dbStringProperty::find(modinst, "implements_operator")` is non-null. The property value is not inspected; it is only logged.
- Otherwise true if the master name has prefix `ALU_` (`strncmp`, 4 characters) or `MACC_` (5 characters).

**6. `doSwapInstances`**
- Iterate the instances. Skip with a warning if the master is null (RSZ-157).
- `produceNewModuleName(old_name, new_name, target)`.
- If the name changed:
  - Take `old_master->getOwner()`, a `dbBlock`. Null gives RSZ-158 and a skip.
  - `block->findModule(new_name)`. A missing module gives RSZ-159 and a skip.
  - Call `inst->swapMaster(new_master)`. If it returns non-null, increment `swapped_count` and record the new instance.
- Replace `insts` with the set of new instances.
- Log RSZ-160 and the metric, and return `swapped_count > 0`.

**7. `produceNewModuleName`**
- Default: `new_name = old_name`. An empty name returns immediately.
- Only `target == "setup"` is handled. Any other target calls `logger_->error(RSZ, 155)`, which throws. Tcl accepts `hold`, `power` and `area`, so those pass the Tcl check and then error here.
- ALU: the name must start with `ALU_`. Look for the first of `"HAN_CARLSON"`, `"BRENT_KUNG"`, `"SKLANSKY"` (checked in that order). On a hit the new name is `old_name.substr(0, pos) + "KOGGE_STONE"`. Everything after the match is dropped.
  - Names already containing `KOGGE_STONE`, or any other type such as ripple, are left unchanged.
- MACC: the name must start with `MACC_`. If it contains `"BOOTH"`, the new name is the prefix before `BOOTH` plus `"BASE"`. The code comment says "Han-Carlson BASE", but the string is just `BASE`.
- The target names must already exist as modules in the same `dbBlock`, as pre-generated variants.

## Key data structures
- `odb::PtrSet<odb::dbModInst>` is the work set. It is a pointer-keyed set, so iteration order is pointer-based and not stable between runs.
- `vector<pair<Vertex*, Slack>>` holds the violating endpoints and is stable-sorted.
- `sta::PathExpanded` is the per-path expansion.
- Members (from the base class `SwapArithModules`): `resizer_`, `db_network_`, `logger_`, `min_`, `max_`. `ConcreteSwapArithModules` adds `init_`. The class derives from `sta::dbStaState`, which provides `sta_` and `network_`.
- Constants: `MAX_HIER_DEPTH = 100`, `ALU_TARGET = "KOGGE_STONE"`, `MACC_TARGET = "BASE"`, and the property key `"implements_operator"`.

## Callers and callees (verified by reading)
- **Caller:** `Resizer::swapArithModules` (`Resizer.cc:5599`) calls `replaceArithModules`. `Resizer::findArithBoundaryPin` (`Resizer.cc:4119`) calls `isArithInstance`. The Tcl and SWIG chain is `Resizer.tcl:1102` → `rsz::swap_arith_modules_cmd` (`Resizer.i:694`) → `Resizer::swapArithModules`. Tests are `test/replace_arith_modules{1,2,3}`.
- **STA callees:** `Sta::updateTiming`, `endpoints`, `slack`, `vertexWorstSlackPath`, `PathExpanded`, `Path::vertex`, `Vertex::pin` and `Vertex::name`, `Network::direction`, `instance`, `parent` and `name`. These sit in the `Sta.cc`, `Search.cc`, `PathExpanded.cc`, `Graph.cc`, `Delay.cc` and `PathEnd.cc` headers' territory. The last two are only included, not actually called.
- **odb / db_sta callees:** `dbNetwork::staToDb`, `dbStringProperty::find`, `dbModInst::getMaster`, `dbModule::getOwner` and `getName`, `dbBlock::findModule`, `dbModInst::swapMaster`.
- **Other:** `Logger` (`info`, `warn`, `error`, `metric`, `debugCheck`). It accesses private `Resizer` members (`logger_`, `sta_`, `db_network_`) through `friend class ConcreteSwapArithModules`.
- `MakeWireParasitics.h` is not included in this file. The parasitics work happens in the Resizer wrapper.

## Invariants and "do not break"
- **No journaling or rollback.** The swap is unconditional and not evaluated. `Resizer::swapArithModules` does not open a journal or undo on worse QoR. Adding any "try then revert" logic must be built outside this file, and swapping back requires the old module name to still exist.
- **STA and parasitics refresh is the caller's job.** After any swap the order must be `ensureLevelized()`, `updateParasitics()`, `clearLogicConstants()`, `updateTiming(true)`, `findRequireds()`. An incremental update is documented in the code as incomplete for this change.
- **`swapMaster` can return a different `dbModInst*`.** The old pointer must be treated as invalid, which is why `insts` is rebuilt from the new instances. Any other cached pointer to the old inst becomes stale.
- **Determinism:** the endpoint order is a stable sort on slack, but `PtrSet` iteration is pointer-ordered. Swap order does not change the result, since each swap is independent and keyed by name. Log order may differ between runs.
- **`dont_touch` is not checked** anywhere in this file.
- **Legality and placement are not touched.** There is no placement or DRC step. The new variant's leaf cells must already be handled by the odb `swapMaster` and placement flow outside this file.
- `init()` must be called before `logger_` or `network_` is used. The public entry points `replaceArithModules` and `isArithInstance` do this. `findCriticalInstances`, `collectArithInstsOnPath`, `doSwapInstances` and `hasArithOperatorProperty` do not call it, so calling them first dereferences a null `logger_`.

## Weak spots / assumptions an algorithm designer should know
- **Only the setup target is implemented, and it is not wired to the real timing model.** The swap is a fixed lookup. There is no delay or area estimate. Swapping can worsen area, power or congestion, and the result is never compared with the old slack.
- **Hold, power and area are advertised by Tcl but throw RSZ-155.** `parse_key_args` accepts them first, and the error happens after the instances are collected and RSZ-151 to 154 are logged.
- **The name convention is a hard dependency.** The variants (`KOGGE_STONE`, `BASE`) must be pre-generated in the netlist or hierarchy, which in practice means the Yosys-side flow with this naming. If they are absent, the code warns RSZ-159 and silently continues.
- **Matching is by `find` and `substr`.** A module whose name merely contains `BRENT_KUNG` (such as a prefix of a longer token) is rewritten, and everything after the match is truncated. Parameter suffixes after the type are lost, so a width suffix could be dropped. This is fine only if the type is the last token.
- **A property match does not guarantee a swap.** An `implements_operator` property marks an instance as arithmetic, but unless the master name begins with `ALU_` or `MACC_` the name mapping is a no-op. The count and metric reflect actual swaps only.
- **Critical selection is endpoint-based.** It takes the worst path per endpoint only (no multiple paths per endpoint, no path-count slack weighting) and includes every arithmetic module on the path regardless of its share of the delay. A module only partly on the path still counts as soon as any output pin on the path is inside it. An arithmetic module nested in another one yields only the innermost one, since `isArithInstance` stops at the first match.
- **Modest scale limits.** There is one STA slack query per endpoint (all endpoints are scanned, not just the worst `path_count`). `vertexWorstSlackPath` returns a pointer that is assumed to be non-null; the code does not check for null, so an endpoint with no path would crash in `PathExpanded`.
- **Flat designs are skipped.** Without hierarchy (`dbModInst`), nothing is found and the function returns false. The command also requires a hierarchical netlist loaded by `read_def` or odb.
- **Misleading comment:** the "Han-Carlson BASE" comment on the MACC swap does not match the actual `BASE` string.
- The swap is purely structural, so parasitics for the new leaf instances come from the Resizer-side `updateParasitics()`. If the design is routed (global or detailed parasitics), the cell set changes without any re-route, and the estimates can be stale.