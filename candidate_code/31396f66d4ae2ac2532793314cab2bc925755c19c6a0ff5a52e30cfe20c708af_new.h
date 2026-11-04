// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73650165;
  double density_weight = 0.12819627;
  double prefix_weight = 0.49963449;
  double neighborhood_weight = 0.12032594;
  double late_weight = 0.14312320;
  double critical_weight = 0.46880595;
  unsigned budget = 8;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
