// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82599038;
  double density_weight = 0.48017732;
  double prefix_weight = 0.32315773;
  double neighborhood_weight = 0.08834428;
  double late_weight = 0.12126344;
  double critical_weight = 0.35005821;
  unsigned budget = 27;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
