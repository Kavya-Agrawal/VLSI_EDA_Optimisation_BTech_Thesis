// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98299834;
  double density_weight = 0.02857542;
  double prefix_weight = 0.08767543;
  double neighborhood_weight = 0.07823543;
  double late_weight = 0.24802717;
  double critical_weight = 0.38474347;
  unsigned budget = 22;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
