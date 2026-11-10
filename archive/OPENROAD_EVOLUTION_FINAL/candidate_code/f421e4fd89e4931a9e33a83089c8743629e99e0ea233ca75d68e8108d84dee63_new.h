// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89252617;
  double density_weight = 0.22710329;
  double prefix_weight = 0.17381121;
  double neighborhood_weight = 0.17974748;
  double late_weight = 0.16943501;
  double critical_weight = 0.28163472;
  unsigned budget = 26;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
