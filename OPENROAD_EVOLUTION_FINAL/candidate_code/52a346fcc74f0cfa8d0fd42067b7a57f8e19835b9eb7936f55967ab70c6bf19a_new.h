// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01084940;
  double density_weight = 0.43130914;
  double prefix_weight = 0.36635269;
  double neighborhood_weight = 0.39746750;
  double late_weight = 0.22648178;
  double critical_weight = 0.40262072;
  unsigned budget = 34;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
