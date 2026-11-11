// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66786852;
  double density_weight = 0.30976397;
  double prefix_weight = 0.22679860;
  double neighborhood_weight = 0.31787888;
  double late_weight = 0.02186590;
  double critical_weight = 0.04949162;
  unsigned budget = 8;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
