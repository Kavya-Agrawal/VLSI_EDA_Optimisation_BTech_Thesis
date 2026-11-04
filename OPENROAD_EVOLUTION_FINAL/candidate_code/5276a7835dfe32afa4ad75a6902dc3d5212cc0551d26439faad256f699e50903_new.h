// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61339092;
  double density_weight = 0.59447627;
  double prefix_weight = 0.14669392;
  double neighborhood_weight = 0.27070943;
  double late_weight = 0.14072251;
  double critical_weight = 0.42620883;
  unsigned budget = 6;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
