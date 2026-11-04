// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77004172;
  double density_weight = 0.21079149;
  double prefix_weight = 0.01748855;
  double neighborhood_weight = 0.07123903;
  double late_weight = 0.29987040;
  double critical_weight = 0.34591630;
  unsigned budget = 24;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
