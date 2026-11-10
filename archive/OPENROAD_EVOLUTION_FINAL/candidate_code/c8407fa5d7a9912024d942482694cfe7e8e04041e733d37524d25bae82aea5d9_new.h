// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96072463;
  double density_weight = 0.57874644;
  double prefix_weight = 0.25522830;
  double neighborhood_weight = 0.33030276;
  double late_weight = 0.05405454;
  double critical_weight = 0.44077828;
  unsigned budget = 35;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
