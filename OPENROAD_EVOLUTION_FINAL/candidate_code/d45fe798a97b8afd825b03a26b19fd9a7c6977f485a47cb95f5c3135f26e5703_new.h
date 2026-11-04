// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21334239;
  double density_weight = 0.25971564;
  double prefix_weight = 0.43452441;
  double neighborhood_weight = 0.18977000;
  double late_weight = 0.27362006;
  double critical_weight = 0.11273477;
  unsigned budget = 23;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
