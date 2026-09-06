# PGR-DRC: Pre-Global Routing DRC Violation Prediction Using Unsupervised Learning

- **Authors:** Riadul Islam, Dhandeep Challagundla (Univ. of Maryland, Baltimore County)
- **Venue / Year:** 2025 (arXiv)
- **PDF:** `PGR-DRC_UnsupervisedDRC_2025.pdf`
- **Link:** https://arxiv.org/abs/2507.13355

---

## TL;DR (one breath)
Predict where **Design Rule Check (DRC) violations** will occur **before global routing** — and do it with **unsupervised learning**, so you don't need expensive labeled violation data. Catching hotspots early avoids costly place-and-route iterations.

## The problem (plain English)
**DRC violations** (illegal geometry/spacing) are usually found **late**, after routing. Fixing them means looping all the way back → slow. Predicting them earlier is valuable, but **labeled** violation data is scarce and expensive to produce.

## Key idea — unsupervised early prediction
Instead of training on labeled "violation / no-violation" examples, use **unsupervised learning** (clustering / density / anomaly-style methods) on pre-routing layout features to **flag likely DRC-hotspot regions** before global routing even runs.

## How it works
1. Extract features from the **pre-global-routing** layout (density, pin/wire distributions, congestion proxies).
2. Apply **unsupervised** models to identify regions that look like future violation hotspots.
3. Surface these early so designers/tools can preempt them.

## Results
- Identifies DRC-prone regions **pre-global-routing** without labeled data.
- Aims to **cut place-and-route iterations** by catching problems early.

## Why it matters for your BTP
- Shows the **label-free** angle — attractive because getting labeled EDA data is the perennial bottleneck.
- Complements **CircuitNet** (which is supervised): a contrast in methodology worth discussing in a thesis.

## Limitations
- Unsupervised flags are **noisier** than supervised predictions (no ground truth to calibrate).
- Newer/less battle-tested than RouteNet-style supervised congestion/DRC CNNs.

## Mini-glossary
- **DRC:** Design Rule Check — manufacturability geometry rules.
- **Global routing:** coarse grid-level wire planning done before detailed routing.
- **Unsupervised learning:** learning structure/patterns without labeled examples.
