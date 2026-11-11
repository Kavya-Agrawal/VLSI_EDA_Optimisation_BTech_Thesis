// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54561831;
  double density_weight = 0.06602156;
  double prefix_weight = 0.09455974;
  double neighborhood_weight = 0.02774624;
  double late_weight = 0.20899252;
  double critical_weight = 0.40191511;
  unsigned budget = 31;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
