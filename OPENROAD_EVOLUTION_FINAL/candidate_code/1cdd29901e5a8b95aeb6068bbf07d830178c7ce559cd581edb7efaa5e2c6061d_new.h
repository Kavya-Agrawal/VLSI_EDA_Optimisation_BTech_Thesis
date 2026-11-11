// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80239028;
  double density_weight = 0.58392111;
  double prefix_weight = 0.09711915;
  double neighborhood_weight = 0.12693086;
  double late_weight = 0.27809540;
  double critical_weight = 0.41916705;
  unsigned budget = 29;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
