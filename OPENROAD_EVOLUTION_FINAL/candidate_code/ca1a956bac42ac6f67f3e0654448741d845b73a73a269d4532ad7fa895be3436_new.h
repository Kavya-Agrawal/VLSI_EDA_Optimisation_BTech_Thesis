// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36369866;
  double density_weight = 0.36085229;
  double prefix_weight = 0.33828708;
  double neighborhood_weight = 0.31735869;
  double late_weight = 0.20771577;
  double critical_weight = 0.43781554;
  unsigned budget = 15;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
