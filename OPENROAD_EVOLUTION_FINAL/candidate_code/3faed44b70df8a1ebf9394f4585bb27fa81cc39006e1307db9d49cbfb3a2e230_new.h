// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30360899;
  double density_weight = 0.16687649;
  double prefix_weight = 0.33186110;
  double neighborhood_weight = 0.23316344;
  double late_weight = 0.26463950;
  double critical_weight = 0.21752787;
  unsigned budget = 8;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
