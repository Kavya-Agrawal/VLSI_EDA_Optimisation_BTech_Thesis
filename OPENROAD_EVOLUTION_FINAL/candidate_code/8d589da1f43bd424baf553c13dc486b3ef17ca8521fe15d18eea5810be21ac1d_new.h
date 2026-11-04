// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58963430;
  double density_weight = 0.47706234;
  double prefix_weight = 0.05842299;
  double neighborhood_weight = 0.13710167;
  double late_weight = 0.09984742;
  double critical_weight = 0.14180383;
  unsigned budget = 7;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
