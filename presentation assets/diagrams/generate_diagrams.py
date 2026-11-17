#!/usr/bin/env python3
"""
Generates production-grade SVG diagrams matching the exact visual style,
colors, spacing, and minimalist aesthetic of Eraser.io reference drawings.
"""

import os
import subprocess

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
OUTPUT_DIR = SCRIPT_DIR

# ==============================================================================
# DIAGRAM 1: TOP-LEVEL EDA FLOW & OPEN-SOURCE TOOLS
# ==============================================================================
def generate_eda_flow_svg():
    svg = """<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 1280 500" width="1280" height="500">
  <defs>
    <marker id="arrow" viewBox="0 0 10 10" refX="7" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
      <path d="M 0 1.5 L 8 5 L 0 8.5 z" fill="#1e293b"/>
    </marker>
    <filter id="soft-shadow" x="-4%" y="-4%" width="108%" height="108%">
      <feDropShadow dx="0" dy="2" stdDeviation="3" flood-color="#000000" flood-opacity="0.04"/>
    </filter>
  </defs>

  <!-- Background -->
  <!-- transparent background for perfect cropping -->

  <!-- Global Flow Title Pill -->
  <g transform="translate(490, 20)">
    <rect width="300" height="32" rx="16" fill="#f8fafc" stroke="#cbd5e1" stroke-width="1.2"/>
    <text x="150" y="21" font-family="system-ui, -apple-system, sans-serif" font-size="13" font-weight="600" fill="#475569" text-anchor="middle">
      Top-Level Digital EDA Physical Design Pipeline
    </text>
  </g>

  <!-- Left Input Arrow: RTL -->
  <line x1="30" y1="260" x2="85" y2="260" stroke="#1e293b" stroke-width="2" marker-end="url(#arrow)"/>
  <rect x="25" y="215" width="55" height="28" rx="6" fill="#f8fafc" stroke="#cbd5e1" stroke-width="1"/>
  <text x="52" y="233" font-family="system-ui, -apple-system, sans-serif" font-size="11" font-weight="600" fill="#334155" text-anchor="middle">RTL (.v)</text>

  <!-- ==================== STAGE 1: LOGIC SYNTHESIS (BLUE) ==================== -->
  <g transform="translate(90, 75)">
    <!-- Pill Badge -->
    <rect x="55" y="-12" width="150" height="24" rx="6" fill="#f8fafc" stroke="#cbd5e1" stroke-width="1"/>
    <text x="130" y="4" font-family="system-ui, -apple-system, sans-serif" font-size="11" font-weight="600" fill="#475569" text-anchor="middle">Stage 1: Front-End</text>

    <!-- Outer Container -->
    <rect width="260" height="380" rx="14" fill="#dbeafe" stroke="#1e293b" stroke-width="1.8" filter="url(#soft-shadow)"/>
    <text x="130" y="38" font-family="system-ui, -apple-system, sans-serif" font-size="16" font-weight="700" fill="#0f172a" text-anchor="middle">
      Logic Synthesis
    </text>
    <text x="130" y="56" font-family="system-ui, -apple-system, sans-serif" font-size="12" font-weight="500" fill="#475569" text-anchor="middle">
      &amp; Technology Mapping
    </text>

    <!-- Inner Card 1: Core Operations -->
    <g transform="translate(18, 75)">
      <rect width="224" height="130" rx="9" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="15" y="24" font-family="system-ui, -apple-system, sans-serif" font-size="13" font-weight="700" fill="#0f172a">Core Operations</text>
      <text x="15" y="48" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• RTL elaboration &amp; parsing</text>
      <text x="15" y="68" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Boolean cut-based rewriting</text>
      <text x="15" y="88" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• AIG optimization (logic depth)</text>
      <text x="15" y="108" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Standard-cell library mapping</text>
    </g>

    <!-- Inner Card 2: Open Source Tools -->
    <g transform="translate(18, 220)">
      <rect width="224" height="135" rx="9" fill="#fef9c3" stroke="#1e293b" stroke-width="1.4"/>
      <text x="15" y="24" font-family="system-ui, -apple-system, sans-serif" font-size="13" font-weight="700" fill="#854d0e">Open-Source EDA Tools</text>
      
      <rect x="15" y="38" width="194" height="38" rx="6" fill="#ffffff" stroke="#eab308" stroke-width="1.2"/>
      <text x="25" y="54" font-family="system-ui, -apple-system, sans-serif" font-size="12" font-weight="700" fill="#0f172a">Yosys</text>
      <text x="25" y="68" font-family="system-ui, -apple-system, sans-serif" font-size="10.5" fill="#64748b">RTL elaboration &amp; generic synth</text>

      <rect x="15" y="84" width="194" height="38" rx="6" fill="#ffffff" stroke="#eab308" stroke-width="1.2"/>
      <text x="25" y="100" font-family="system-ui, -apple-system, sans-serif" font-size="12" font-weight="700" fill="#0f172a">ABC</text>
      <text x="25" y="114" font-family="system-ui, -apple-system, sans-serif" font-size="10.5" fill="#64748b">AIG rewriting &amp; tech mapping</text>
    </g>
  </g>

  <!-- Arrow 1 -> 2: Gate-Level Netlist -->
  <line x1="350" y1="260" x2="385" y2="260" stroke="#1e293b" stroke-width="2" marker-end="url(#arrow)"/>
  <rect x="345" y="225" width="40" height="24" rx="5" fill="#f8fafc" stroke="#cbd5e1" stroke-width="1"/>
  <text x="365" y="241" font-family="system-ui, -apple-system, sans-serif" font-size="9.5" font-weight="600" fill="#475569" text-anchor="middle">.v</text>

  <!-- ==================== STAGE 2: PHYSICAL PLACEMENT (GREY) ==================== -->
  <g transform="translate(390, 75)">
    <!-- Pill Badge -->
    <rect x="55" y="-12" width="150" height="24" rx="6" fill="#f8fafc" stroke="#cbd5e1" stroke-width="1"/>
    <text x="130" y="4" font-family="system-ui, -apple-system, sans-serif" font-size="11" font-weight="600" fill="#475569" text-anchor="middle">Stage 2: Spatial Layout</text>

    <!-- Outer Container -->
    <rect width="260" height="380" rx="14" fill="#f1f5f9" stroke="#1e293b" stroke-width="1.8" filter="url(#soft-shadow)"/>
    <text x="130" y="38" font-family="system-ui, -apple-system, sans-serif" font-size="16" font-weight="700" fill="#0f172a" text-anchor="middle">
      Floorplan &amp; Placement
    </text>
    <text x="130" y="56" font-family="system-ui, -apple-system, sans-serif" font-size="12" font-weight="500" fill="#475569" text-anchor="middle">
      Global &amp; Detailed Legalization
    </text>

    <!-- Inner Card 1: Core Operations -->
    <g transform="translate(18, 75)">
      <rect width="224" height="130" rx="9" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="15" y="24" font-family="system-ui, -apple-system, sans-serif" font-size="13" font-weight="700" fill="#0f172a">Core Operations</text>
      <text x="15" y="48" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Die area &amp; I/O pin assignment</text>
      <text x="15" y="68" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Global analytical wirelength (ePlace)</text>
      <text x="15" y="88" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Detailed standard-cell row snap</text>
      <text x="15" y="108" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Zero-overlap legalization</text>
    </g>

    <!-- Inner Card 2: Open Source Tools -->
    <g transform="translate(18, 220)">
      <rect width="224" height="135" rx="9" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="15" y="24" font-family="system-ui, -apple-system, sans-serif" font-size="13" font-weight="700" fill="#0f172a">Open-Source EDA Tools</text>
      
      <rect x="15" y="38" width="194" height="38" rx="6" fill="#f8fafc" stroke="#94a3b8" stroke-width="1.2"/>
      <text x="25" y="54" font-family="system-ui, -apple-system, sans-serif" font-size="12" font-weight="700" fill="#0f172a">RePlAce</text>
      <text x="25" y="68" font-family="system-ui, -apple-system, sans-serif" font-size="10.5" fill="#64748b">Global electrostatics placement</text>

      <rect x="15" y="84" width="194" height="38" rx="6" fill="#f8fafc" stroke="#94a3b8" stroke-width="1.2"/>
      <text x="25" y="100" font-family="system-ui, -apple-system, sans-serif" font-size="12" font-weight="700" fill="#0f172a">OpenDP</text>
      <text x="25" y="114" font-family="system-ui, -apple-system, sans-serif" font-size="10.5" fill="#64748b">Detailed legalizer &amp; site alignment</text>
    </g>
  </g>

  <!-- Arrow 2 -> 3: Placed Layout -->
  <line x1="650" y1="260" x2="685" y2="260" stroke="#1e293b" stroke-width="2" marker-end="url(#arrow)"/>
  <rect x="642" y="225" width="46" height="24" rx="5" fill="#f8fafc" stroke="#cbd5e1" stroke-width="1"/>
  <text x="665" y="241" font-family="system-ui, -apple-system, sans-serif" font-size="9.5" font-weight="600" fill="#475569" text-anchor="middle">.def</text>

  <!-- ==================== STAGE 3: ROUTING (GREY) ==================== -->
  <g transform="translate(690, 75)">
    <!-- Pill Badge -->
    <rect x="55" y="-12" width="150" height="24" rx="6" fill="#f8fafc" stroke="#cbd5e1" stroke-width="1"/>
    <text x="130" y="4" font-family="system-ui, -apple-system, sans-serif" font-size="11" font-weight="600" fill="#475569" text-anchor="middle">Stage 3: Interconnect</text>

    <!-- Outer Container -->
    <rect width="260" height="380" rx="14" fill="#f1f5f9" stroke="#1e293b" stroke-width="1.8" filter="url(#soft-shadow)"/>
    <text x="130" y="38" font-family="system-ui, -apple-system, sans-serif" font-size="16" font-weight="700" fill="#0f172a" text-anchor="middle">
      Routing Engine
    </text>
    <text x="130" y="56" font-family="system-ui, -apple-system, sans-serif" font-size="12" font-weight="500" fill="#475569" text-anchor="middle">
      Global &amp; Detailed Routing
    </text>

    <!-- Inner Card 1: Core Operations -->
    <g transform="translate(18, 75)">
      <rect width="224" height="130" rx="9" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="15" y="24" font-family="system-ui, -apple-system, sans-serif" font-size="13" font-weight="700" fill="#0f172a">Core Operations</text>
      <text x="15" y="48" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Global grid congestion estimation</text>
      <text x="15" y="68" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Track assignment across metal layers</text>
      <text x="15" y="88" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Detailed pin-to-pin wiring</text>
      <text x="15" y="108" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• DRC-clean via stacking &amp; enclosure</text>
    </g>

    <!-- Inner Card 2: Open Source Tools -->
    <g transform="translate(18, 220)">
      <rect width="224" height="135" rx="9" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="15" y="24" font-family="system-ui, -apple-system, sans-serif" font-size="13" font-weight="700" fill="#0f172a">Open-Source EDA Tools</text>
      
      <rect x="15" y="38" width="194" height="38" rx="6" fill="#f8fafc" stroke="#94a3b8" stroke-width="1.2"/>
      <text x="25" y="54" font-family="system-ui, -apple-system, sans-serif" font-size="12" font-weight="700" fill="#0f172a">FastRoute</text>
      <text x="25" y="68" font-family="system-ui, -apple-system, sans-serif" font-size="10.5" fill="#64748b">Global routing &amp; congestion map</text>

      <rect x="15" y="84" width="194" height="38" rx="6" fill="#f8fafc" stroke="#94a3b8" stroke-width="1.2"/>
      <text x="25" y="100" font-family="system-ui, -apple-system, sans-serif" font-size="12" font-weight="700" fill="#0f172a">TritonRoute</text>
      <text x="25" y="114" font-family="system-ui, -apple-system, sans-serif" font-size="10.5" fill="#64748b">DRC-clean detailed router</text>
    </g>
  </g>

  <!-- Arrow 3 -> 4: Routed Layout -->
  <line x1="950" y1="260" x2="985" y2="260" stroke="#1e293b" stroke-width="2" marker-end="url(#arrow)"/>
  <rect x="942" y="225" width="46" height="24" rx="5" fill="#f8fafc" stroke="#cbd5e1" stroke-width="1"/>
  <text x="965" y="241" font-family="system-ui, -apple-system, sans-serif" font-size="9.5" font-weight="600" fill="#475569" text-anchor="middle">.spef</text>

  <!-- ==================== STAGE 4: STA & CLOSURE (PINK) ==================== -->
  <g transform="translate(990, 75)">
    <!-- Pill Badge -->
    <rect x="55" y="-12" width="150" height="24" rx="6" fill="#f8fafc" stroke="#cbd5e1" stroke-width="1"/>
    <text x="130" y="4" font-family="system-ui, -apple-system, sans-serif" font-size="11" font-weight="600" fill="#475569" text-anchor="middle">Stage 4: Signoff &amp; Closure</text>

    <!-- Outer Container -->
    <rect width="260" height="380" rx="14" fill="#fecdd3" stroke="#1e293b" stroke-width="1.8" filter="url(#soft-shadow)"/>
    <text x="130" y="38" font-family="system-ui, -apple-system, sans-serif" font-size="16" font-weight="700" fill="#0f172a" text-anchor="middle">
      STA &amp; Timing Closure
    </text>
    <text x="130" y="56" font-family="system-ui, -apple-system, sans-serif" font-size="12" font-weight="500" fill="#475569" text-anchor="middle">
      Analysis &amp; Resizer (rsz)
    </text>

    <!-- Inner Card 1: Core Operations -->
    <g transform="translate(18, 75)">
      <rect width="224" height="130" rx="9" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="15" y="24" font-family="system-ui, -apple-system, sans-serif" font-size="13" font-weight="700" fill="#0f172a">Core Operations</text>
      <text x="15" y="48" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Setup &amp; hold slack calculation</text>
      <text x="15" y="68" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Driver gate sizing &amp; VT swapping</text>
      <text x="15" y="88" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Buffer tree synthesis &amp; repair</text>
      <text x="15" y="108" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Max slew, cap &amp; fanout DRV fixes</text>
    </g>

    <!-- Inner Card 2: Open Source Tools -->
    <g transform="translate(18, 220)">
      <rect width="224" height="135" rx="9" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="15" y="24" font-family="system-ui, -apple-system, sans-serif" font-size="13" font-weight="700" fill="#0f172a">Open-Source EDA Tools</text>
      
      <rect x="15" y="38" width="194" height="38" rx="6" fill="#fff1f2" stroke="#fb7185" stroke-width="1.2"/>
      <text x="25" y="54" font-family="system-ui, -apple-system, sans-serif" font-size="12" font-weight="700" fill="#0f172a">OpenSTA</text>
      <text x="25" y="68" font-family="system-ui, -apple-system, sans-serif" font-size="10.5" fill="#64748b">Golden gate-level timing engine</text>

      <rect x="15" y="84" width="194" height="38" rx="6" fill="#fff1f2" stroke="#fb7185" stroke-width="1.2"/>
      <text x="25" y="100" font-family="system-ui, -apple-system, sans-serif" font-size="12" font-weight="700" fill="#0f172a">OpenROAD Resizer (rsz)</text>
      <text x="25" y="114" font-family="system-ui, -apple-system, sans-serif" font-size="10.5" fill="#64748b">Post-placement timing repair</text>
    </g>
  </g>

  <!-- Right Output Arrow: GDSII -->
  <line x1="1250" y1="260" x2="1275" y2="260" stroke="#1e293b" stroke-width="2"/>
</svg>
"""
    file_path = os.path.join(OUTPUT_DIR, "eda_flow_overview.svg")
    with open(file_path, "w", encoding="utf-8") as f:
        f.write(svg)
    print(f"Generated {file_path}")
    return file_path


# ==============================================================================
# DIAGRAM 2: OPENROAD VS ABC COMPARISON
# ==============================================================================
def generate_openroad_vs_abc_svg():
    svg = """<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 1280 560" width="1280" height="560">
  <defs>
    <marker id="arrow" viewBox="0 0 10 10" refX="7" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
      <path d="M 0 1.5 L 8 5 L 0 8.5 z" fill="#1e293b"/>
    </marker>
    <filter id="soft-shadow" x="-4%" y="-4%" width="108%" height="108%">
      <feDropShadow dx="0" dy="2" stdDeviation="3" flood-color="#000000" flood-opacity="0.04"/>
    </filter>
  </defs>

  <!-- Background -->
  <!-- transparent background for perfect cropping -->

  <!-- Global Header Pill -->
  <g transform="translate(460, 18)">
    <rect width="360" height="32" rx="16" fill="#f8fafc" stroke="#cbd5e1" stroke-width="1.2"/>
    <text x="180" y="21" font-family="system-ui, -apple-system, sans-serif" font-size="13" font-weight="600" fill="#475569" text-anchor="middle">
      Architectural Comparison: Logic Synthesis vs. Physical Design
    </text>
  </g>

  <!-- ==================== COLUMN 1: ABC (BLUE) ==================== -->
  <g transform="translate(60, 75)">
    <!-- Pill Badge -->
    <rect x="80" y="-12" width="200" height="24" rx="6" fill="#f8fafc" stroke="#cbd5e1" stroke-width="1"/>
    <text x="180" y="4" font-family="system-ui, -apple-system, sans-serif" font-size="11" font-weight="600" fill="#475569" text-anchor="middle">Logic Synthesis Domain</text>

    <!-- Outer Container -->
    <rect width="360" height="450" rx="14" fill="#dbeafe" stroke="#1e293b" stroke-width="1.8" filter="url(#soft-shadow)"/>
    <text x="180" y="38" font-family="system-ui, -apple-system, sans-serif" font-size="18" font-weight="700" fill="#0f172a" text-anchor="middle">
      ABC / Self-Evolved ABC
    </text>
    <text x="180" y="56" font-family="system-ui, -apple-system, sans-serif" font-size="12" font-weight="500" fill="#475569" text-anchor="middle">
      Discrete Boolean Logic Optimization
    </text>

    <!-- Sub-card 1: Representation -->
    <g transform="translate(18, 75)">
      <rect width="324" height="74" rx="8" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="14" y="22" font-family="system-ui, -apple-system, sans-serif" font-size="12.5" font-weight="700" fill="#0f172a">Circuit Representation</text>
      <text x="14" y="42" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• And-Inverter Graphs (AIGs) &amp; Boolean truth tables</text>
      <text x="14" y="60" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• No physical layout coordinates, no RC parasitics</text>
    </g>

    <!-- Sub-card 2: Oracle -->
    <g transform="translate(18, 160)">
      <rect width="324" height="88" rx="8" fill="#fef9c3" stroke="#1e293b" stroke-width="1.4"/>
      <text x="14" y="22" font-family="system-ui, -apple-system, sans-serif" font-size="12.5" font-weight="700" fill="#854d0e">Correctness Oracle: Single SAT Miter</text>
      <text x="14" y="42" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Combinational Equivalence Checking (CEC)</text>
      <text x="14" y="60" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Math guarantee: ∀ x, F_orig(x) == F_evolved(x)</text>
      <text x="14" y="78" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" font-weight="600" fill="#854d0e">• Single binary verdict: UNSAT = PASS</text>
    </g>

    <!-- Sub-card 3: Search Plasticity -->
    <g transform="translate(18, 260)">
      <rect width="324" height="82" rx="8" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="14" y="22" font-family="system-ui, -apple-system, sans-serif" font-size="12.5" font-weight="700" fill="#0f172a">Agent Search Plasticity</text>
      <text x="14" y="42" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• High local freedom: unconstrained cut restructuring</text>
      <text x="14" y="60" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Edits in abci/ do not cause physical violations</text>
      <text x="14" y="76" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Instant verification (&lt; 1 sec per testcase)</text>
    </g>

    <!-- Sub-card 4: Benchmarks -->
    <g transform="translate(18, 354)">
      <rect width="324" height="74" rx="8" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="14" y="22" font-family="system-ui, -apple-system, sans-serif" font-size="12.5" font-weight="700" fill="#0f172a">Standard Benchmarks</text>
      <text x="14" y="42" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• ISCAS'85, ISCAS'89, EPFL benchmark suites</text>
      <text x="14" y="60" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Logic netlists without process design kits (PDKs)</text>
    </g>
  </g>

  <!-- ==================== COLUMN 2: KEY DIVERGENCE (GREY) ==================== -->
  <g transform="translate(460, 75)">
    <!-- Pill Badge -->
    <rect x="75" y="-12" width="210" height="24" rx="6" fill="#f8fafc" stroke="#cbd5e1" stroke-width="1"/>
    <text x="180" y="4" font-family="system-ui, -apple-system, sans-serif" font-size="11" font-weight="600" fill="#475569" text-anchor="middle">The Physical Reality Barrier</text>

    <!-- Outer Container -->
    <rect width="360" height="450" rx="14" fill="#f1f5f9" stroke="#1e293b" stroke-width="1.8" filter="url(#soft-shadow)"/>
    <text x="180" y="38" font-family="system-ui, -apple-system, sans-serif" font-size="18" font-weight="700" fill="#0f172a" text-anchor="middle">
      Why Logic != Physical
    </text>
    <text x="180" y="56" font-family="system-ui, -apple-system, sans-serif" font-size="12" font-weight="500" fill="#475569" text-anchor="middle">
      Fundamental EDA Domain Shift
    </text>

    <!-- Comparison Row 1 -->
    <g transform="translate(18, 75)">
      <rect width="324" height="74" rx="8" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="14" y="22" font-family="system-ui, -apple-system, sans-serif" font-size="12.5" font-weight="700" fill="#0f172a">Boolean Logic vs. Silicon Physics</text>
      <text x="14" y="42" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• ABC preserves functional truth tables.</text>
      <text x="14" y="60" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• OpenROAD must obey non-linear nanometer physics.</text>
    </g>

    <!-- Comparison Row 2 -->
    <g transform="translate(18, 160)">
      <rect width="324" height="88" rx="8" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="14" y="22" font-family="system-ui, -apple-system, sans-serif" font-size="12.5" font-weight="700" fill="#0f172a">Oracle: Single SAT vs. Multi-Domain</text>
      <text x="14" y="42" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• CEC cannot detect overlapping placed cells.</text>
      <text x="14" y="60" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• CEC cannot detect slew degradation or hold violations.</text>
      <text x="14" y="78" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" font-weight="600" fill="#0f172a">• Physical tools require orthogonal verification layers.</text>
    </g>

    <!-- Comparison Row 3 -->
    <g transform="translate(18, 260)">
      <rect width="324" height="82" rx="8" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="14" y="22" font-family="system-ui, -apple-system, sans-serif" font-size="12.5" font-weight="700" fill="#0f172a">Coupled Non-Local Side Effects</text>
      <text x="14" y="42" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Sizing gate g increases its input capacitance C_in.</text>
      <text x="14" y="60" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Higher C_in slows upstream driver, rippling delay back.</text>
      <text x="14" y="76" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Wider cell displaces adjacent cells, risking DRC overlaps.</text>
    </g>

    <!-- Comparison Row 4 -->
    <g transform="translate(18, 354)">
      <rect width="324" height="74" rx="8" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="14" y="22" font-family="system-ui, -apple-system, sans-serif" font-size="12.5" font-weight="700" fill="#0f172a">Search Space Constraints</text>
      <text x="14" y="42" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Random edits produce 96.1% invalid or regressed designs.</text>
      <text x="14" y="60" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Guided physical path mutation (TPGM) is mandatory.</text>
    </g>
  </g>

  <!-- ==================== COLUMN 3: OPENROAD (PINK) ==================== -->
  <g transform="translate(860, 75)">
    <!-- Pill Badge -->
    <rect x="80" y="-12" width="200" height="24" rx="6" fill="#f8fafc" stroke="#cbd5e1" stroke-width="1"/>
    <text x="180" y="4" font-family="system-ui, -apple-system, sans-serif" font-size="11" font-weight="600" fill="#475569" text-anchor="middle">Physical Design Domain</text>

    <!-- Outer Container -->
    <rect width="360" height="450" rx="14" fill="#fecdd3" stroke="#1e293b" stroke-width="1.8" filter="url(#soft-shadow)"/>
    <text x="180" y="38" font-family="system-ui, -apple-system, sans-serif" font-size="18" font-weight="700" fill="#0f172a" text-anchor="middle">
      OpenROAD / PV-Evolve
    </text>
    <text x="180" y="56" font-family="system-ui, -apple-system, sans-serif" font-size="12" font-weight="500" fill="#475569" text-anchor="middle">
      2D Layout &amp; Timing Closure Engine (rsz)
    </text>

    <!-- Sub-card 1: Representation -->
    <g transform="translate(18, 75)">
      <rect width="324" height="74" rx="8" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="14" y="22" font-family="system-ui, -apple-system, sans-serif" font-size="12.5" font-weight="700" fill="#0f172a">Circuit Representation</text>
      <text x="14" y="42" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Geometric layout (.def / .odb) with (X, Y) coordinates</text>
      <text x="14" y="60" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Liberty non-linear tables (.lib) &amp; wire parasitics (.spef)</text>
    </g>

    <!-- Sub-card 2: Oracle -->
    <g transform="translate(18, 160)">
      <rect width="324" height="88" rx="8" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="14" y="22" font-family="system-ui, -apple-system, sans-serif" font-size="12.5" font-weight="700" fill="#9f1239">Correctness Oracle: 6-Layer PVCC</text>
      <text x="14" y="42" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• C(c, r) = L1(build) ∧ L2(unit) ∧ L3(OpenDP legal)</text>
      <text x="14" y="60" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">          ∧ L4(DRC slew/cap) ∧ L5(Hold) ∧ L6(determ)</text>
      <text x="14" y="78" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" font-weight="600" fill="#9f1239">• Fail-Closed: any violation aborts evaluation</text>
    </g>

    <!-- Sub-card 3: Search Plasticity -->
    <g transform="translate(18, 260)">
      <rect width="324" height="82" rx="8" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="14" y="22" font-family="system-ui, -apple-system, sans-serif" font-size="12.5" font-weight="700" fill="#0f172a">Agent Search Plasticity</text>
      <text x="14" y="42" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Constrained physical moves (sizing, buffering, hold)</text>
      <text x="14" y="60" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Guided by TPGM path sensitivity matrix w_i</text>
      <text x="14" y="76" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Bounded code context dossiers via Graphify</text>
    </g>

    <!-- Sub-card 4: Benchmarks -->
    <g transform="translate(18, 354)">
      <rect width="324" height="74" rx="8" fill="#ffffff" stroke="#1e293b" stroke-width="1.4"/>
      <text x="14" y="22" font-family="system-ui, -apple-system, sans-serif" font-size="12.5" font-weight="700" fill="#0f172a">Standard Benchmarks</text>
      <text x="14" y="42" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Real ASIC placed blocks: Nangate45 GCD, AES, Ibex</text>
      <text x="14" y="60" font-family="system-ui, -apple-system, sans-serif" font-size="11.5" fill="#334155">• Advanced nodes: ASAP7 (7nm FinFET), SKY130</text>
    </g>
  </g>
</svg>
"""
    file_path = os.path.join(OUTPUT_DIR, "openroad_vs_abc_comparison.svg")
    with open(file_path, "w", encoding="utf-8") as f:
        f.write(svg)
    print(f"Generated {file_path}")
    return file_path

if __name__ == "__main__":
    f1 = generate_eda_flow_svg()
    f2 = generate_openroad_vs_abc_svg()
