// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46874320;
  double density_weight = 0.25152648;
  double prefix_weight = 0.44397007;
  double neighborhood_weight = 0.09527680;
  double late_weight = 0.18836495;
  double critical_weight = 0.11685268;
  unsigned budget = 9;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
