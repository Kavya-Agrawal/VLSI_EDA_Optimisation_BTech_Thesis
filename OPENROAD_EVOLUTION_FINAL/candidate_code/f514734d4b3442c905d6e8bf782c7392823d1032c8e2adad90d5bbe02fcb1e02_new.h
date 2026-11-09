// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73256262;
  double density_weight = 0.58694272;
  double prefix_weight = 0.27122885;
  double neighborhood_weight = 0.33094493;
  double late_weight = 0.25107000;
  double critical_weight = 0.10358706;
  unsigned budget = 14;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
