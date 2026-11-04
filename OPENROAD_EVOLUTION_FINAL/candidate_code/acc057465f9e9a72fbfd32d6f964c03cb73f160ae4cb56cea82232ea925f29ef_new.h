// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79716723;
  double density_weight = 0.46798663;
  double prefix_weight = 0.03336343;
  double neighborhood_weight = 0.16809265;
  double late_weight = 0.02001011;
  double critical_weight = 0.44872658;
  unsigned budget = 19;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
