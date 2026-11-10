// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06900403;
  double density_weight = 0.28449434;
  double prefix_weight = 0.21006008;
  double neighborhood_weight = 0.13020724;
  double late_weight = 0.10291987;
  double critical_weight = 0.49814282;
  unsigned budget = 12;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
