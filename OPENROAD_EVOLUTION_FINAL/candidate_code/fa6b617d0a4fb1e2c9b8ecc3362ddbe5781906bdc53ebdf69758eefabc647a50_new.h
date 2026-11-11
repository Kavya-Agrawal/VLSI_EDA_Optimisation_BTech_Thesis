// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67747532;
  double density_weight = 0.48415790;
  double prefix_weight = 0.28728868;
  double neighborhood_weight = 0.22152458;
  double late_weight = 0.28025246;
  double critical_weight = 0.05919475;
  unsigned budget = 14;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
