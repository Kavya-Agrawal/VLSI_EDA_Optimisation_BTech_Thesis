// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98548287;
  double density_weight = 0.32435168;
  double prefix_weight = 0.44225114;
  double neighborhood_weight = 0.22506902;
  double late_weight = 0.18116133;
  double critical_weight = 0.09637994;
  unsigned budget = 22;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
