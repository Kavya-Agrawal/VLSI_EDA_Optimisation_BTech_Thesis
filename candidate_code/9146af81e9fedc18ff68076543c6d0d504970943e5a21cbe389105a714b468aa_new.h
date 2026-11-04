// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74118282;
  double density_weight = 0.39488257;
  double prefix_weight = 0.29083477;
  double neighborhood_weight = 0.08389951;
  double late_weight = 0.22025376;
  double critical_weight = 0.35770573;
  unsigned budget = 20;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
