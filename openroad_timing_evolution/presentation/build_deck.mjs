import fs from "node:fs/promises";
import path from "node:path";
import { pathToFileURL } from "node:url";
import { Presentation, PresentationFile } from "@oai/artifact-tool";

const ROOT = path.resolve(new URL(".", import.meta.url).pathname, "..");
const SKILL_DIR = "/home/kavya-kumar-agrawal/.codex/plugins/cache/openai-primary-runtime/presentations/26.903.11726/skills/presentations";
const RUNTIME_PYTHON = "/home/kavya-kumar-agrawal/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3";
const TMP_DIR = path.join(ROOT, "presentation", ".build");
const FINAL_PPTX = path.join(ROOT, "output", "openroad_timing_evolution_framework.pptx");
const FINAL_DIR = path.dirname(FINAL_PPTX);
const { resolvePresentationFont, finalizePresentation } = await import(
  pathToFileURL(path.join(SKILL_DIR, "container_tools/artifact_tool_utils.mjs")).href
);

await fs.mkdir(TMP_DIR, { recursive: true });
await fs.mkdir(FINAL_DIR, { recursive: true });
try { await fs.rm(FINAL_PPTX); } catch {}

const font = resolvePresentationFont({ fontFamily: "Aptos" });
const p = Presentation.create({ slideSize: { width: 1280, height: 720 } });
const navy = "#0B1F33";
const teal = "#0D9488";
const blue = "#2563EB";
const gray = "#64748B";
const light = "#F1F5F9";
const pale = "#ECFEFF";
const red = "#B91C1C";

function addText(slide, text, x, y, w, h, size = 24, color = navy, opts = {}) {
  const box = slide.shapes.add({
    geometry: "textbox",
    position: { left: x, top: y, width: w, height: h },
    fill: "none",
    line: { fill: "none", width: 0 },
  });
  box.text = text;
  box.text.style = {
    typeface: font,
    fontSize: size,
    bold: Boolean(opts.bold),
    italic: Boolean(opts.italic),
    color,
    autoFit: "shrinkText",
  };
  return box;
}

function addTitle(slide, title, kicker) {
  addText(slide, title, 70, 46, 820, 58, 35, navy, { bold: true });
  if (kicker) addText(slide, kicker, 72, 104, 900, 34, 18, gray);
}

function rect(slide, x, y, w, h, fill, line = "#CBD5E1") {
  return slide.shapes.add({
    geometry: "rect",
    position: { left: x, top: y, width: w, height: h },
    fill,
    line: { fill: line, width: 1 },
  });
}

function line(slide, x, y, w, color = gray) {
  slide.shapes.add({
    geometry: "rect",
    position: { left: x, top: y, width: w, height: 3 },
    fill: color,
    line: { fill: color, width: 0 },
  });
}

function foot(slide, n) {
  addText(slide, `OpenROAD timing evolution framework    ${n}`, 70, 670, 1120, 22, 12, gray);
}

function notes(slide, text) {
  slide.speakerNotes.textFrame.setText(text);
}

function slide1() {
  const s = p.slides.add();
  s.background.fill = "#FFFFFF";
  addText(s, "Algorithmic Evolution Framework for OpenROAD Timing Closure", 70, 82, 1000, 120, 42, navy, { bold: true });
  addText(s, "Bounded policy evolution for resizer path-driver ordering, with strict WNS/TNS and physical-correctness gates", 72, 214, 850, 70, 22, gray);
  rect(s, 70, 365, 260, 78, pale, teal);
  addText(s, "Target", 92, 378, 170, 24, 17, teal, { bold: true });
  addText(s, "OpenROAD resizer setup repair ordering", 92, 405, 205, 30, 17, navy);
  rect(s, 370, 365, 260, 78, "#EFF6FF", blue);
  addText(s, "Objective", 392, 378, 170, 24, 17, blue, { bold: true });
  addText(s, "Paired setup WNS/TNS improvement", 392, 405, 205, 30, 17, navy);
  rect(s, 670, 365, 300, 78, "#FEF2F2", red);
  addText(s, "Guardrails", 692, 378, 170, 24, 17, red, { bold: true });
  addText(s, "No timing, DRC, formal or provenance failures", 692, 405, 245, 30, 17, navy);
  foot(s, 1);
  notes(s, "Sources: OpenROAD resizer documentation; AlphaEvolve, Novikov et al. 2025; VPR-Evolve, Wu et al. 2026; Autonomous Evolution of EDA Tools, Yu and Ren 2026; EvoDRC, Wu et al. 2026.");
}

function slide2() {
  const s = p.slides.add();
  s.background.fill = "#FFFFFF";
  addTitle(s, "Research Pattern", "The papers converge on one useful rule: evolve small executable code, then judge it with hard tests.");
  const labels = [
    ["AlphaEvolve", "Executable code candidates with automated correctness checks"],
    ["VPR-Evolve", "Pinned baselines, held-out designs and rejected-history logging"],
    ["EDA tool evolution", "Compile and QoR loops around real EDA source"],
    ["EvoDRC", "Bounded layout edits with strict physical checks"],
  ];
  labels.forEach((item, i) => {
    const x = 90 + i * 285;
    rect(s, x, 210, 230, 160, i % 2 ? "#EFF6FF" : pale, i % 2 ? blue : teal);
    addText(s, item[0], x + 18, 230, 190, 32, 21, navy, { bold: true });
    addText(s, item[1], x + 18, 275, 190, 70, 17, gray);
  });
  line(s, 150, 455, 960, navy);
  addText(s, "Framework translation", 90, 490, 270, 30, 22, teal, { bold: true });
  addText(s, "Bounded expression grammar, isolated build, frozen audit binary, train/validation/test split and fail-closed metrics.", 370, 486, 760, 42, 21, navy);
  foot(s, 2);
  notes(s, "Sources: AlphaEvolve arXiv:2506.13131; VPR-Evolve arXiv:2607.24998; Autonomous Evolution of EDA Tools arXiv:2604.15082; EvoDRC arXiv:2607.20019.");
}

function slide3() {
  const s = p.slides.add();
  s.background.fill = "#FFFFFF";
  addTitle(s, "OpenROAD Code Target", "The patch reorders existing resizer repair targets. It does not create timing objects or rewrite OpenROAD source freely.");
  rect(s, 90, 205, 260, 100, light);
  addText(s, "Stock path analysis", 112, 225, 210, 28, 21, navy, { bold: true });
  addText(s, "Critical path plus latch fanin context", 112, 262, 200, 28, 17, gray);
  line(s, 350, 254, 95, gray);
  rect(s, 445, 205, 305, 100, pale, teal);
  addText(s, "Generated policy", 467, 225, 220, 28, 21, navy, { bold: true });
  addText(s, "Priority over load, fanout and original position", 467, 262, 245, 28, 17, gray);
  line(s, 750, 254, 95, gray);
  rect(s, 845, 205, 300, 100, "#EFF6FF", blue);
  addText(s, "Repair committer", 867, 225, 220, 28, 21, navy, { bold: true });
  addText(s, "Uses the unchanged OpenROAD repair machinery", 867, 262, 240, 28, 17, gray);
  addText(s, "Changed file", 105, 410, 160, 24, 18, teal, { bold: true });
  addText(s, "src/rsz/src/policy/SetupLegacyBase.cc", 260, 410, 760, 24, 19, navy);
  addText(s, "Generated file", 105, 454, 160, 24, 18, teal, { bold: true });
  addText(s, "src/rsz/src/policy/EvolvedPathDriverPolicy.h", 260, 454, 760, 24, 19, navy);
  foot(s, 3);
  notes(s, "Sources: OpenROAD resizer documentation and local OpenROAD source patch in openroad_timing_evolution/patches/path_driver_policy.patch.");
}

function slide4() {
  const s = p.slides.add();
  s.background.fill = "#FFFFFF";
  addTitle(s, "Candidate Space", "The framework evolves formulas, not arbitrary patches.");
  const rows = [
    ["Features", "load, fanout, position"],
    ["Operators", "add, sub, mul, min, max"],
    ["Limits", "depth 5, 31 nodes, constants in [-4, 4]"],
    ["Policy ID", "SHA-256 of canonical JSON"],
  ];
  rows.forEach((r, i) => {
    rect(s, 120, 190 + i * 82, 1040, 58, i % 2 ? "#FFFFFF" : light);
    addText(s, r[0], 150, 204 + i * 82, 210, 25, 20, teal, { bold: true });
    addText(s, r[1], 380, 204 + i * 82, 680, 25, 20, navy);
  });
  addText(s, "Example candidate: load + 0.25 * fanout", 122, 560, 620, 34, 24, blue, { bold: true });
  addText(s, "Every candidate must compile and match the Python reference before any flow run starts.", 122, 604, 760, 30, 19, gray);
  foot(s, 4);
  notes(s, "Sources: local implementation in openroad_timing_evolution/policy.py and openroad_timing_evolution/cpp/policy.h.in.");
}

function slide5() {
  const s = p.slides.add();
  s.background.fill = "#FFFFFF";
  addTitle(s, "End-to-End Evaluation", "A candidate earns timing score only after real flow evidence passes.");
  const steps = ["Policy JSON", "C++ header", "OpenROAD build", "ORFS run", "Frozen audit", "Formal proof", "Paired score"];
  steps.forEach((step, i) => {
    const x = 72 + i * 170;
    rect(s, x, 260, 136, 80, i === 4 ? "#FEF2F2" : i % 2 ? "#EFF6FF" : pale, i === 4 ? red : i % 2 ? blue : teal);
    addText(s, step, x + 12, 285, 108, 28, 17, navy, { bold: true });
    if (i < steps.length - 1) line(s, x + 136, 298, 34, gray);
  });
  addText(s, "Score", 120, 430, 130, 28, 23, teal, { bold: true });
  addText(s, "0.5 * delta WNS / period  +  0.5 * delta TNS / period endpoints", 250, 430, 810, 30, 22, navy);
  addText(s, "Any failed correctness gate records a rejection and returns no performance score.", 120, 505, 820, 30, 20, gray);
  foot(s, 5);
  notes(s, "Sources: local evaluator implementation in openroad_timing_evolution/runner.py and metrics.py.");
}

function slide6() {
  const s = p.slides.add();
  s.background.fill = "#FFFFFF";
  addTitle(s, "Correctness Gates", "The framework rejects incomplete or inconsistent evidence before comparing WNS/TNS.");
  const gates = [
    ["Timing", "No setup or hold WNS/TNS regression on paired runs"],
    ["Physical", "Zero placement, route DRC, antenna and electrical violations"],
    ["Equivalence", "Yosys proves final Verilog against post-synthesis Verilog"],
    ["Provenance", "Candidate, audit binary and evaluator protocol hashes stay fixed"],
  ];
  gates.forEach((g, i) => {
    const x = i < 2 ? 100 : 680;
    const y = i % 2 ? 390 : 210;
    rect(s, x, y, 480, 110, i % 2 ? "#EFF6FF" : pale, i % 2 ? blue : teal);
    addText(s, g[0], x + 24, y + 20, 200, 26, 23, navy, { bold: true });
    addText(s, g[1], x + 24, y + 58, 390, 28, 18, gray);
  });
  foot(s, 6);
  notes(s, "Sources: local evaluator implementation in openroad_timing_evolution/metrics.py, runner.py and tcl/audit.tcl.");
}

function slide7() {
  const s = p.slides.add();
  s.background.fill = "#FFFFFF";
  addTitle(s, "Experiment Protocol", "Training can guide the search. Validation and test results cannot feed back into parent selection.");
  const cols = [
    ["Train", "gcd", "Evolve and rank parents"],
    ["Validation", "aes", "Open after finalist freezes"],
    ["Test", "ibex", "Final sealed check"],
  ];
  cols.forEach((c, i) => {
    const x = 120 + i * 350;
    rect(s, x, 220, 280, 210, i === 0 ? pale : i === 1 ? "#EFF6FF" : "#FEF2F2", i === 0 ? teal : i === 1 ? blue : red);
    addText(s, c[0], x + 26, 245, 200, 30, 26, navy, { bold: true });
    addText(s, c[1], x + 26, 300, 170, 34, 32, i === 0 ? teal : i === 1 ? blue : red, { bold: true });
    addText(s, c[2], x + 26, 365, 210, 35, 18, gray);
  });
  addText(s, "Default smoke config uses three replicas per design and rejects duplicate or incomplete matrices.", 120, 525, 860, 28, 20, navy);
  foot(s, 7);
  notes(s, "Sources: local config in openroad_timing_evolution/config/smoke.json and search implementation in openroad_timing_evolution/search.py.");
}

function slide8() {
  const s = p.slides.add();
  s.background.fill = "#FFFFFF";
  addTitle(s, "Delivered Branch", "The branch contains the framework, tests, docs and this deck.");
  const items = [
    ["Branch", "btp/rsz-path-driver-evolution"],
    ["Framework", "openroad_timing_evolution/"],
    ["Tests run", "12 local tests passed"],
    ["Docker doctor", "Pinned image and toolchain check passed"],
    ["Full QoR status", "Ready to run through evolve, not claimed complete here"],
  ];
  items.forEach((it, i) => {
    addText(s, it[0], 105, 185 + i * 72, 210, 24, 20, teal, { bold: true });
    addText(s, it[1], 330, 185 + i * 72, 760, 24, 20, navy);
  });
  addText(s, "Command: python3 -m openroad_timing_evolution --config openroad_timing_evolution/config/smoke.json evolve --generations 3 --population 4", 105, 578, 980, 48, 18, gray);
  foot(s, 8);
  notes(s, "Validation performed during wrap-up: python3 -m openroad_timing_evolution selftest; python3 -m openroad_timing_evolution propose/check; python3 -m openroad_timing_evolution --config openroad_timing_evolution/config/smoke.json doctor.");
}

[slide1, slide2, slide3, slide4, slide5, slide6, slide7, slide8].forEach(fn => fn());

const stagingDir = path.join(ROOT, "presentation", ".codex-finalizer");
await fs.mkdir(stagingDir, { recursive: true });
const candidatePath = path.join(stagingDir, "candidate.pptx");
await (await PresentationFile.exportPptx(p)).save(candidatePath);

const requirements = {
  explicitTotalSlideCount: 8,
  requiredNativeTableOwnerSlides: [],
  requiredNativeChartOwnerSlides: [],
};
const result = await finalizePresentation({
  ...requirements,
  workspaceDir: ROOT,
  candidatePath,
  finalPath: FINAL_PPTX,
  pythonExecutable: RUNTIME_PYTHON,
  integrityValidatorPath: path.join(SKILL_DIR, "container_tools/inspect_presentation_package_integrity.py"),
  layoutValidatorPath: path.join(SKILL_DIR, "container_tools/inspect_presentation_layout_geometry.py"),
  layoutArgs: [
    "--expected-slide-size-emu", "12192000,6858000",
    "--validate-bullet-geometry",
    "--validate-heading-fit",
  ],
  fontPolicy: { basis: "design", families: [font] },
  verifyArtifactToolImport: true,
  receiptPath: path.join(stagingDir, "openroad_timing_evolution_framework.validation.json"),
});

const imported = await PresentationFile.importPptx(await (await import("@oai/artifact-tool")).FileBlob.load(FINAL_PPTX));
const renderDir = path.join(ROOT, "presentation", ".build", "rendered");
await fs.mkdir(renderDir, { recursive: true });
for (let i = 0; i < imported.slides.length; i++) {
  const preview = await imported.export({ slide: imported.slides.get(i), format: "png", scale: 1 });
  await fs.writeFile(path.join(renderDir, `slide-${String(i + 1).padStart(2, "0")}.png`), new Uint8Array(await preview.arrayBuffer()));
}
console.log(JSON.stringify({ final: FINAL_PPTX, renderDir, validation: result }, null, 2));
