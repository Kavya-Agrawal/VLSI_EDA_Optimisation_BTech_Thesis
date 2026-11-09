// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53513312;
  double density_weight = 0.18129976;
  double prefix_weight = 0.31574873;
  double neighborhood_weight = 0.26751465;
  double late_weight = 0.10191016;
  double critical_weight = 0.15454214;
  unsigned budget = 33;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
