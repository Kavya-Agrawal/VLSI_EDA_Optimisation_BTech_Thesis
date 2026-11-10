// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98502008;
  double density_weight = 0.10906073;
  double prefix_weight = 0.11022182;
  double neighborhood_weight = 0.11922593;
  double late_weight = 0.24059494;
  double critical_weight = 0.07104219;
  unsigned budget = 7;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
