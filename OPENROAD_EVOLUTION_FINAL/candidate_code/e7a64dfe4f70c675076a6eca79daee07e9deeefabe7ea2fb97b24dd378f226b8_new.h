// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65458436;
  double density_weight = 0.54900955;
  double prefix_weight = 0.34482721;
  double neighborhood_weight = 0.22414442;
  double late_weight = 0.14623869;
  double critical_weight = 0.14166438;
  unsigned budget = 15;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
