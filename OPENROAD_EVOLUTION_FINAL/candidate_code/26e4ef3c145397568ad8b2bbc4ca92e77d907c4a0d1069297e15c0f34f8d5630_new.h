// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47163273;
  double density_weight = 0.42852614;
  double prefix_weight = 0.19516111;
  double neighborhood_weight = 0.04360554;
  double late_weight = 0.29035297;
  double critical_weight = 0.05949252;
  unsigned budget = 25;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
