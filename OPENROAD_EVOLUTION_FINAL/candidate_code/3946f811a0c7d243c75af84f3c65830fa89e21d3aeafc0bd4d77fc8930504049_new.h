// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92548542;
  double density_weight = 0.13926751;
  double prefix_weight = 0.46052859;
  double neighborhood_weight = 0.03510368;
  double late_weight = 0.26711301;
  double critical_weight = 0.04801916;
  unsigned budget = 19;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
