// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66469027;
  double density_weight = 0.06014857;
  double prefix_weight = 0.46101774;
  double neighborhood_weight = 0.11792840;
  double late_weight = 0.25743103;
  double critical_weight = 0.25128251;
  unsigned budget = 31;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
