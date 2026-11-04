// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80923925;
  double density_weight = 0.16947253;
  double prefix_weight = 0.25851193;
  double neighborhood_weight = 0.22048067;
  double late_weight = 0.18386814;
  double critical_weight = 0.17851299;
  unsigned budget = 19;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
