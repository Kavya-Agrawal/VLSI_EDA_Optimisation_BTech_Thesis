// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62444159;
  double density_weight = 0.23765629;
  double prefix_weight = 0.20621799;
  double neighborhood_weight = 0.15004658;
  double late_weight = 0.22892830;
  double critical_weight = 0.18297471;
  unsigned budget = 13;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
