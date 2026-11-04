// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59595226;
  double density_weight = 0.45012588;
  double prefix_weight = 0.02615500;
  double neighborhood_weight = 0.05082221;
  double late_weight = 0.06250176;
  double critical_weight = 0.07791286;
  unsigned budget = 8;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
