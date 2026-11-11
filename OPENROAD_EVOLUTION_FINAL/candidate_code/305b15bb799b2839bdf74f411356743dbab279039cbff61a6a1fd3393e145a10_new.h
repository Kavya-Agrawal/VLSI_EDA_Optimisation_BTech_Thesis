// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16871380;
  double density_weight = 0.56951573;
  double prefix_weight = 0.20242590;
  double neighborhood_weight = 0.39180242;
  double late_weight = 0.04889607;
  double critical_weight = 0.04720748;
  unsigned budget = 14;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
