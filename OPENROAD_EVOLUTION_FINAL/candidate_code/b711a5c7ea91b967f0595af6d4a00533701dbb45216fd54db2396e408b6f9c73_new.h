// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39228379;
  double density_weight = 0.46648601;
  double prefix_weight = 0.02249765;
  double neighborhood_weight = 0.24639437;
  double late_weight = 0.24413814;
  double critical_weight = 0.47566492;
  unsigned budget = 18;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
