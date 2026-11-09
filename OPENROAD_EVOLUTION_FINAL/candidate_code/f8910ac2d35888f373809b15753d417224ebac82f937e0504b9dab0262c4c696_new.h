// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54174132;
  double density_weight = 0.37088403;
  double prefix_weight = 0.41114324;
  double neighborhood_weight = 0.36757825;
  double late_weight = 0.17520318;
  double critical_weight = 0.28117249;
  unsigned budget = 26;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
