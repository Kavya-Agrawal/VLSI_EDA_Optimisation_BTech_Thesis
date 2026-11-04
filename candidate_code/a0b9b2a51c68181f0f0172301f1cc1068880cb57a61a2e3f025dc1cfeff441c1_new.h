// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14320376;
  double density_weight = 0.40901324;
  double prefix_weight = 0.25326310;
  double neighborhood_weight = 0.28713374;
  double late_weight = 0.02074491;
  double critical_weight = 0.39974077;
  unsigned budget = 8;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
