// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74186304;
  double density_weight = 0.10323904;
  double prefix_weight = 0.25142135;
  double neighborhood_weight = 0.17485716;
  double late_weight = 0.23708130;
  double critical_weight = 0.48849098;
  unsigned budget = 8;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
