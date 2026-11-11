// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19694599;
  double density_weight = 0.46622891;
  double prefix_weight = 0.39854065;
  double neighborhood_weight = 0.19651810;
  double late_weight = 0.22853008;
  double critical_weight = 0.24250054;
  unsigned budget = 40;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
