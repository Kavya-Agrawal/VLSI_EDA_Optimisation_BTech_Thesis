// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23021890;
  double density_weight = 0.38397772;
  double prefix_weight = 0.13497243;
  double neighborhood_weight = 0.05226149;
  double late_weight = 0.06192803;
  double critical_weight = 0.42288695;
  unsigned budget = 38;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
