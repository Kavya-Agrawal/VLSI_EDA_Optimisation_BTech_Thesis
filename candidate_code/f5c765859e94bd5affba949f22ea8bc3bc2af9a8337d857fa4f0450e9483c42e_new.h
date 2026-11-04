// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42502617;
  double density_weight = 0.43887750;
  double prefix_weight = 0.20589701;
  double neighborhood_weight = 0.29199171;
  double late_weight = 0.08964711;
  double critical_weight = 0.13431298;
  unsigned budget = 35;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
