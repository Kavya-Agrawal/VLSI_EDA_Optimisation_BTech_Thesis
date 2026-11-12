"""Produce placed checkpoints with ORFS (synth -> floorplan -> global place -> repair_design -> detailed
place, *without* repair_timing) and calibrate a `stressed.sdc` so the stock resizer is left with real
negative slack to repair.

    make checkpoints TIER=A      ->  04_benchmarks/designs/<pdk>/<design>/{placed.odb,nominal.sdc,stressed.sdc,design.json}

ORFS is driven exactly as a user would: `make -C flow DESIGN_CONFIG=... place` with
ENABLE_PLACE_REPAIR_TIMING=0, OPENROAD_EXE/YOSYS_EXE pointing at our binaries and WORK_HOME under
04_benchmarks/orfs_runs/ so nothing is written into the submodule."""
from __future__ import annotations

import re
import shutil
from pathlib import Path
from typing import Any

from ..config import PATHS, Knobs, designs_for_tier
from ..util import log, now_iso, read_json, run, write_json, write_text
from .run_eval import Design, run_one

STRESS_RATIOS = [0.90, 0.80, 0.70, 0.60, 0.50, 0.40]


def orfs_make(design_key: str, target: str, *, extra: dict[str, str] | None = None, timeout: int = 7200) -> tuple[Path, Path, "RunResult"]:
    pdk, name = design_key.split("/")
    flow = PATHS.orfs_src / "flow"
    cfg = flow / "designs" / pdk / name / "config.mk"
    if not cfg.exists():
        raise FileNotFoundError(f"no ORFS design config at {cfg}")
    work = PATHS.orfs_runs / f"{pdk}__{name}"
    work.mkdir(parents=True, exist_ok=True)
    cmd = ["make", "-C", flow, f"DESIGN_CONFIG={cfg}", f"WORK_HOME={work}",
           f"OPENROAD_EXE={PATHS.openroad_stock}", f"YOSYS_EXE={PATHS.yosys}", "ENABLE_PLACE_REPAIR_TIMING=0"]
    for k, v in (extra or {}).items():
        cmd.append(f"{k}={v}")
    cmd.append(target)
    log(f"ORFS {design_key}: make {target} (work={work.relative_to(PATHS.root)})")
    res = run(cmd, timeout=timeout, log_file=work / f"make_{target}.log")
    return work, cfg, res


def orfs_var(design_key: str, var: str) -> str:
    """Ask the ORFS Makefile for a resolved variable (print-% target)."""
    pdk, name = design_key.split("/")
    flow = PATHS.orfs_src / "flow"
    cfg = flow / "designs" / pdk / name / "config.mk"
    res = run(["make", "-s", "-C", flow, f"DESIGN_CONFIG={cfg}", f"print-{var}"], timeout=120)
    for line in res.stdout.splitlines():
        if line.startswith(f"{var} = "):
            return line[len(var) + 3:].strip()
    return ""


def results_dir(work: Path, design_key: str) -> Path:
    pdk, name = design_key.split("/")
    nick = orfs_var(design_key, "DESIGN_NICKNAME") or name
    return work / "results" / pdk / nick / "base"


def scale_sdc(src: Path, dst: Path, ratio: float) -> float:
    """Copy an SDC scaling every create_clock -period by `ratio`. Returns the (largest) new period."""
    text = src.read_text()
    periods: list[float] = []

    def repl(m: re.Match) -> str:
        p = float(m.group(2)) * ratio
        periods.append(p)
        return f"{m.group(1)}{p:.6g}"
    out = re.sub(r"(create_clock[^\n]*?-period\s+)([0-9.eE+-]+)", repl, text)
    # ORFS constraint.sdc style: set clk_period X
    out = re.sub(r"(set\s+clk_period\s+)([0-9.eE+-]+)", lambda m: (periods.append(float(m.group(2)) * ratio) or f"{m.group(1)}{float(m.group(2))*ratio:.6g}"), out)
    write_text(dst, f"# derived from {src.name} with clock periods scaled by {ratio}\n" + out)
    return max(periods) if periods else 0.0


def sdc_period(p: Path) -> float:
    text = p.read_text()
    vals = [float(x) for x in re.findall(r"create_clock[^\n]*?-period\s+([0-9.eE+-]+)", text)]
    vals += [float(x) for x in re.findall(r"set\s+clk_period\s+([0-9.eE+-]+)", text)]
    return max(vals) if vals else 0.0


def make_checkpoint(design_key: str, knobs: Knobs, *, force: bool = False, calibrate: bool = True) -> dict[str, Any]:
    pdk, name = design_key.split("/")
    ddir = PATHS.designs / pdk / name
    meta_path = ddir / "design.json"
    if meta_path.exists() and (ddir / "placed.odb").exists() and not force:
        log(f"{design_key}: checkpoint exists (use --force to regenerate)")
        return read_json(meta_path)
    work, cfg, res = orfs_make(design_key, "place", timeout=knobs.build_timeout_s)
    rdir = results_dir(work, design_key)
    odb, sdc = rdir / "3_5_place_dp.odb", rdir / "3_place.sdc"
    if not res.ok or not odb.exists():
        raise RuntimeError(f"ORFS place failed for {design_key}; see {work}/make_place.log (rc={res.returncode})")
    ddir.mkdir(parents=True, exist_ok=True)
    shutil.copy2(odb, ddir / "placed.odb")
    shutil.copy2(sdc, ddir / "nominal.sdc")
    libs = orfs_var(design_key, "LIB_FILES").split()
    platform_dir = orfs_var(design_key, "PLATFORM_DIR")
    set_rc = orfs_var(design_key, "LAYER_PARASITICS_FILE") or f"{platform_dir}/setRC.tcl"
    meta = {
        "pdk": pdk, "design": name, "top": orfs_var(design_key, "DESIGN_NAME"),
        "odb": "placed.odb", "sdc": {"nominal": "nominal.sdc"},
        "libs": libs, "set_rc": set_rc, "dont_use": orfs_var(design_key, "DONT_USE_CELLS"),
        "clock_period_ns": {"nominal": sdc_period(ddir / "nominal.sdc")},
        "provenance": {"orfs_config": str(cfg), "orfs_results": str(rdir), "generated": now_iso(),
                       "openroad": str(PATHS.openroad_stock), "stage": "3_5_place_dp (ENABLE_PLACE_REPAIR_TIMING=0)",
                       "instances": None},
    }
    write_json(meta_path, meta)
    log(f"{design_key}: checkpoint written ({(ddir/'placed.odb').stat().st_size/1e6:.1f} MB), nominal period {meta['clock_period_ns']['nominal']}")
    if calibrate:
        calibrate_stress(design_key, knobs)
    return read_json(meta_path)


def calibrate_stress(design_key: str, knobs: Knobs) -> dict[str, Any]:
    """Find the largest clock-period scale factor whose stock post-repair WNS is at most
    knobs.stressed_wns_target_ratio * period (i.e. clearly negative), and write stressed.sdc."""
    pdk, name = design_key.split("/")
    ddir = PATHS.designs / pdk / name
    meta = read_json(ddir / "design.json")
    d = Design(design_key, ddir, meta)
    cal_dir = ddir / "calibration"
    chosen: dict[str, Any] | None = None
    table: list[dict[str, Any]] = []
    for ratio in STRESS_RATIOS:
        tmp = cal_dir / f"stress_{ratio:.2f}.sdc"
        period = scale_sdc(ddir / "nominal.sdc", tmp, ratio)
        r = run_one(PATHS.openroad_stock, d, "nominal", cal_dir / f"r{ratio:.2f}", knobs, sdc_override=tmp)
        if not r.ok:
            table.append({"ratio": ratio, "period": period, "ok": False, "error": r.error}); continue
        wns_post, tns_post = float(r.post["wns_setup"]), float(r.post["tns_setup"])
        wns_pre = float(r.pre["wns_setup"])
        row = {"ratio": ratio, "period": period, "ok": True, "wns_pre": wns_pre, "wns_post": wns_post, "tns_post": tns_post,
               "wns_post_pct_period": 100.0 * wns_post / period if period else 0.0}
        table.append(row)
        log(f"{design_key}: ratio {ratio:.2f} period {period:.4g}: WNS {wns_pre:+.4f} -> {wns_post:+.4f} ({row['wns_post_pct_period']:+.1f}% of period)")
        if period and wns_post <= knobs.stressed_wns_target_ratio * period:
            chosen = row
            break
    if chosen is None:
        ok_rows = [t for t in table if t.get("ok")]
        chosen = min(ok_rows, key=lambda t: t["wns_post"]) if ok_rows else None
    if chosen is None:
        raise RuntimeError(f"{design_key}: could not calibrate a stressed SDC; see {cal_dir}")
    scale_sdc(ddir / "nominal.sdc", ddir / "stressed.sdc", chosen["ratio"])
    meta["sdc"]["stressed"] = "stressed.sdc"
    meta["clock_period_ns"]["stressed"] = chosen["period"]
    meta["stress_calibration"] = {"chosen_ratio": chosen["ratio"], "target_wns_ratio": knobs.stressed_wns_target_ratio,
                                  "table": table, "binary": str(PATHS.openroad_stock), "when": now_iso()}
    write_json(ddir / "design.json", meta)
    log(f"{design_key}: stressed.sdc = nominal x {chosen['ratio']:.2f} (period {chosen['period']:.4g}, stock post-repair WNS {chosen['wns_post']:+.4f})")
    return meta


def make_tier(tier: str, knobs: Knobs, *, only: list[str] | None = None, force: bool = False, calibrate: bool = True) -> None:
    keys = only or designs_for_tier(tier)
    done, failed = [], []
    for k in keys:
        try:
            make_checkpoint(k, knobs, force=force, calibrate=calibrate)
            done.append(k)
        except Exception as e:  # keep going; report at the end
            log(f"{k}: FAILED: {e}")
            failed.append((k, str(e)))
    log(f"checkpoints done: {done}; failed: {failed}")
    index = {"generated": now_iso(), "designs": {}}
    for p in sorted(PATHS.designs.glob("*/*/design.json")):
        m = read_json(p)
        index["designs"][f"{m['pdk']}/{m['design']}"] = {"periods": m.get("clock_period_ns"), "ready": (p.parent / "placed.odb").exists()}
    write_json(PATHS.benchmarks / "INDEX.json", index)
    if failed:
        raise SystemExit(1)
