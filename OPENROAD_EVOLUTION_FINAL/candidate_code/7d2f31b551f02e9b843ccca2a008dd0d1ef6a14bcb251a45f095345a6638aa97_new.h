// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04529165;
  double density_weight = 0.36274610;
  double prefix_weight = 0.06754226;
  double neighborhood_weight = 0.05093850;
  double late_weight = 0.03006578;
  double critical_weight = 0.24528944;
  unsigned budget = 39;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
