// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71906465;
  double density_weight = 0.52078811;
  double prefix_weight = 0.42542673;
  double neighborhood_weight = 0.28562264;
  double late_weight = 0.21335742;
  double critical_weight = 0.07422803;
  unsigned budget = 10;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
