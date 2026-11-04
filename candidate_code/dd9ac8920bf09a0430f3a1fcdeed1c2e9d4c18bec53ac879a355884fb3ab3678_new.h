// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46908357;
  double density_weight = 0.48555541;
  double prefix_weight = 0.15605009;
  double neighborhood_weight = 0.31405277;
  double late_weight = 0.15677932;
  double critical_weight = 0.37037589;
  unsigned budget = 20;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
