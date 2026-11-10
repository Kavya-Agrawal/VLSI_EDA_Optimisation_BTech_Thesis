// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99365805;
  double density_weight = 0.31360610;
  double prefix_weight = 0.27529810;
  double neighborhood_weight = 0.04271229;
  double late_weight = 0.23273386;
  double critical_weight = 0.43269712;
  unsigned budget = 32;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
