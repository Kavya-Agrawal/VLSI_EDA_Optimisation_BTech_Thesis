// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63821549;
  double density_weight = 0.29709136;
  double prefix_weight = 0.49210635;
  double neighborhood_weight = 0.09272214;
  double late_weight = 0.03000992;
  double critical_weight = 0.45619845;
  unsigned budget = 9;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
