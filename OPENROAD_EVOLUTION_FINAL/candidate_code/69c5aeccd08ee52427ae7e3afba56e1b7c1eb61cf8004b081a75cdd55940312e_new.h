// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99626940;
  double density_weight = 0.33046914;
  double prefix_weight = 0.37950653;
  double neighborhood_weight = 0.10885423;
  double late_weight = 0.08929933;
  double critical_weight = 0.01612961;
  unsigned budget = 38;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
