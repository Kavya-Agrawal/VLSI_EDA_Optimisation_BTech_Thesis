// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61979423;
  double density_weight = 0.37470297;
  double prefix_weight = 0.31346311;
  double neighborhood_weight = 0.20946288;
  double late_weight = 0.11728139;
  double critical_weight = 0.32519086;
  unsigned budget = 29;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
