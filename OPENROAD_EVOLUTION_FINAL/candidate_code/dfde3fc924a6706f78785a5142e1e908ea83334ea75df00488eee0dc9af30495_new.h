// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60744219;
  double density_weight = 0.15599059;
  double prefix_weight = 0.00346196;
  double neighborhood_weight = 0.09676642;
  double late_weight = 0.02732994;
  double critical_weight = 0.22146549;
  unsigned budget = 31;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
