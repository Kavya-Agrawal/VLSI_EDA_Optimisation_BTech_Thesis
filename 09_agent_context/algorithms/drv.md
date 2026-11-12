<!-- hand-edited -->
# Cluster: `drv` (Design Rule Violation Repair)

This dossier provides the formal engineering specification for the `drv` cluster in OpenROAD's Resizer (`src/rsz`). It governs electrical compliance checking and repair for maximum transition time (`max_slew`), maximum load capacitance (`max_capacitance`), maximum fanout count (`max_fanout`), and maximum wirelength limits.

---

## 1. The Problem (Formal-ish)

### 1.1 Inputs and Outputs
- **Inputs**:
  - Placed design netlist with interconnect parasitics (`odb::dbBlock`, `sta::dbSta`).
  - Library electrical limits defined in Liberty cell descriptions: `max_transition`, `max_capacitance`, and `max_fanout` on library cell output and input pins.
  - SDC design rule overrides: `set_max_transition`, `set_max_capacitance`, `set_max_fanout`.
  - User safety margins (`repair_design` arguments): `-slew_margin`, `-cap_margin`, and `-max_wire_length`.
- **Outputs**:
  - Legalized netlist modifications (buffer insertions, driver resizings, load segmentations) ensuring:
    $$\forall p \in \text{Pins}, \quad t_{\text{slew}}(p) \le t_{\text{max\_slew}}(p) \cdot (1 - \text{slew\_margin})$$
    $$\forall n \in \text{Nets}, \quad C_{\text{load}}(n) \le C_{\text{max\_cap}}(n) \cdot (1 - \text{cap\_margin})$$
    $$\forall p \in \text{DriverPins}, \quad \text{Fanout}(p) \le \text{max\_fanout}(p)$$

---

## 2. Current Algorithm, Step by Step

### 2.1 Top-Level Driver (`rsz::RepairDesign::repairDesign`)
Implemented in `src/RepairDesign.cc:110`:
1. **Preamble and Initialization**:
   - Gathers list of available buffer cells from the active library, filtered by `dont_use` and footprint rules.
   - Computes drive resistance and input capacitance for all candidate buffers.
2. **Slew Limit Pre-Checks (`rsz::PreChecks::checkSlewLimit`)**:
   - Queries `sta::Sta::checkSlew()` across all design pins.
   - Flags driver pins where output transition time exceeds the threshold.
3. **Capacitance Repair (`rsz::RepairDesign::repairCapacitance`)**:
   - Iterates through all design nets.
   - If total load capacitance $C_{\text{wire}} + \sum C_{\text{pin}} > C_{\text{max}}$, constructs a Steiner tree over the net.
   - Inserts buffers along high-capacitance branches or immediately after the driver pin (`repairDriverCap`).
4. **Driver Slew Repair (`rsz::RepairDesign::repairDriverSlew`)**:
   - Evaluates whether up-sizing the existing driver cell to a larger master can resolve the slew violation without adding buffers.
   - If up-sizing is insufficient or unavailable, inserts repeaters along the driving net to isolate downstream load capacitance.
5. **Fanout Repair (`rsz::RepairDesign::repairFanout`)**:
   - Identifies nets where sink count exceeds `max_fanout`.
   - Constructs a balanced buffer tree to partition fanout sinks into clusters smaller than the limit.
6. **Long Wire Repair (`rsz::RepairDesign::repairLongWires`)**:
   - Scans nets exceeding `max_wire_length`.
   - Inserts repeaters at uniform intervals along long wire segments based on technology sheet resistance and capacitance.

---

## 3. Interaction with the Timer and Other Clusters

- **Prerequisite for Timing Repair**: `repair_design` runs before `repair_timing`. Severe slew violations invalidate lookup table interpolations in timing models; fixing DRVs first ensures STA calculations are numerically stable.
- **Parasitics Coupling**: Every buffer inserted during DRV repair splits nets, requiring parasitic invalidation and Steiner tree regeneration.

---

## 4. Known Weaknesses and Failure Modes

1. **Over-Buffering of Short Heavy Nets**: Nets driving multiple small registers are often buffered repeatedly instead of up-sizing the driver or balancing placement.
2. **Timing Unawareness**: Standard DRV repair treats all nets equally, regardless of whether a net has +2.0 ns of slack or -1.0 ns of negative slack, often consuming valuable routing area on non-critical nets.

---

## 5. Alternative Approaches from Literature

### 5.1 Slack-Aware DRV Repair
- **Concept**: Prioritize driver resizing over buffer insertion on timing-critical nets; defer buffer insertion on non-critical nets until power/area budgets are assessed.
- **Injection Point**: Integrate slack queries from `sta::dbSta` inside `src/RepairDesign.cc:checkSlew` to bias repair selection toward minimal area or latency.
- **Expected Gain**: 5–10% lower buffer count and reduced cell density hotspots.

---

## 6. Safe-Change Checklist for `drv`

When modifying code within this cluster, ensure:
- [ ] **No Unchecked Allocations**: Verify `findBufferUnderSlew` handles situations where no library buffer meets extreme slew targets without throwing unhandled exceptions.
- [ ] **Placement Legality**: Ensure newly inserted buffers are legalized via OpenDP before committing.
- [ ] **Regression Tests**: Run `test/repair_design*.tcl`, `test/repair_slew*.tcl`, and `test/repair_cap*.tcl`.
