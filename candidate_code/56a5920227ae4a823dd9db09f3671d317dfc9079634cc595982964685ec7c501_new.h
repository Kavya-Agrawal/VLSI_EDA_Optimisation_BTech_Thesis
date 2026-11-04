// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77642404;
  double density_weight = 0.17645434;
  double prefix_weight = 0.34375179;
  double neighborhood_weight = 0.28126977;
  double late_weight = 0.15606852;
  double critical_weight = 0.36656204;
  unsigned budget = 30;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
