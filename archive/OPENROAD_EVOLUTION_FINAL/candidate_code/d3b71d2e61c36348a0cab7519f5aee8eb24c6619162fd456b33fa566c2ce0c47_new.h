// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94303955;
  double density_weight = 0.54216345;
  double prefix_weight = 0.05502080;
  double neighborhood_weight = 0.11826277;
  double late_weight = 0.00882189;
  double critical_weight = 0.17329355;
  unsigned budget = 13;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
