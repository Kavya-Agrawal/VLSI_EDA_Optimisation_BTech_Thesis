// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13332574;
  double density_weight = 0.36458432;
  double prefix_weight = 0.46030172;
  double neighborhood_weight = 0.05000819;
  double late_weight = 0.28315941;
  double critical_weight = 0.15757306;
  unsigned budget = 5;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
