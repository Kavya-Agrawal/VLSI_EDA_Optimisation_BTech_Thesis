// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17855911;
  double density_weight = 0.55903915;
  double prefix_weight = 0.18682982;
  double neighborhood_weight = 0.22993919;
  double late_weight = 0.25002549;
  double critical_weight = 0.44472017;
  unsigned budget = 21;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
