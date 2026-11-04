// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38263652;
  double density_weight = 0.34134755;
  double prefix_weight = 0.29796568;
  double neighborhood_weight = 0.28339239;
  double late_weight = 0.09724174;
  double critical_weight = 0.13183663;
  unsigned budget = 24;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
