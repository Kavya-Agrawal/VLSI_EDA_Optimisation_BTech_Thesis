# Joint path-window sizing by Viterbi DP in TNS recovery

## Problem
Single-driver upsizing (`SizeUpGenerator::upsizeCell`) is cancelled by the extra
input cap it puts on the upstream stage, so recovery rejects many single moves
(77 WNS rejects on JPEG). Gains that need 2-4 stages sized together are invisible.

## Current heuristic
`src/move/SizeUpGenerator.cc:upsizeCell` picks one master per driver using
`gateDelay + prev_drive*Cin`. `src/policy/SetupLegacyPolicy.cc:runTnsRecovery`
tries one stock move per bottleneck driver (journaled, WNS floor, 0.5 ps TNS gain).

## New approach
In `runTnsRecovery`, for each ranked bottleneck driver and before the stock attempts,
build a window of up to 4 consecutive driver stages on the current worst path to the
driver's worst endpoint. Per stage the candidates are the current master plus the
swappable masters with drive resistance no weaker on both edges (area <= 8x, at most
10, sorted by area/name). A Viterbi DP minimises
sum_i gateDelay(m_i, load = side_i + Cin(m_{i+1}))
+ prev_drive*Cin(m_0) + 0.2*R_prev*max(0,dCin)*side_fanout_prev + small area penalty.
The result is applied as one journaled compound move (several `replaceCell` calls
inside one `committer_.beginJournal()`). It is kept only under the unchanged
stock-WNS floor and 0.5 ps TNS threshold, otherwise the journal is restored and the
stock attempts run as before. Main-phase code is untouched, so stock-phase move
counts are identical.

## Why WNS/TNS should improve
Coordinated upsizing of a driver and its predecessors pays for the added input cap
with a stronger upstream driver, a trade single moves reject. Accepted joint moves
add TNS recovery on deep HA/FA (JPEG) and trunk (Ibex) paths.

## What to look for in the path report
Consecutive cells on one path moving up together (e.g. X1->X2 on 2-4 adjacent
stages), a lower per-stage delay on the upstream cells, and fewer rejected WNS
trials. Counters: `window_dp_*`, `window_joint_changed_vs_greedy`.

## Risks
The estimator ignores slew propagation (`gateDelay` uses default input slew), so
wire-dominated stages can be mis-estimated. Side loads may hit the WNS floor
(counted in `window_dp_rejected_wns`). Extra STA updates add runtime. The window
code lives in `SetupLegacyPolicy.cc`, which is not in the editable list (see notes).

## Files changed
- `src/policy/SetupLegacyPolicy.cc`: DP window planner (lambda `planWindow`), window trial before the stock attempts in `runTnsRecovery`, `window_*` RSZ_EVOLVE counters, endpoint recorded per bottleneck driver.
