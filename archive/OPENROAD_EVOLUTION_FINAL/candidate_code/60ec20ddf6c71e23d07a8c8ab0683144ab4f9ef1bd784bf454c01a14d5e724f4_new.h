// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10684192;
  double density_weight = 0.51699001;
  double prefix_weight = 0.23335337;
  double neighborhood_weight = 0.15475411;
  double late_weight = 0.10734390;
  double critical_weight = 0.15597599;
  unsigned budget = 14;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
