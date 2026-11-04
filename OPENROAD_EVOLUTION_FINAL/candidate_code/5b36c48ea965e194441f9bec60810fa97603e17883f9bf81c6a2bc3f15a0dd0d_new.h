// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65317241;
  double density_weight = 0.17322237;
  double prefix_weight = 0.34011048;
  double neighborhood_weight = 0.17827408;
  double late_weight = 0.29670959;
  double critical_weight = 0.17075664;
  unsigned budget = 40;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
