// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54312349;
  double density_weight = 0.02414380;
  double prefix_weight = 0.29563917;
  double neighborhood_weight = 0.30000015;
  double late_weight = 0.23475320;
  double critical_weight = 0.05561286;
  unsigned budget = 14;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
