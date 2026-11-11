// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59080409;
  double density_weight = 0.11757285;
  double prefix_weight = 0.18514606;
  double neighborhood_weight = 0.08319703;
  double late_weight = 0.16242503;
  double critical_weight = 0.34410867;
  unsigned budget = 27;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
