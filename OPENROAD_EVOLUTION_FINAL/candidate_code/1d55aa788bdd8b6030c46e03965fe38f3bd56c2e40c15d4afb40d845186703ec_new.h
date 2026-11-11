// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43484052;
  double density_weight = 0.49459224;
  double prefix_weight = 0.11485381;
  double neighborhood_weight = 0.16090309;
  double late_weight = 0.05184213;
  double critical_weight = 0.46862722;
  unsigned budget = 24;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
