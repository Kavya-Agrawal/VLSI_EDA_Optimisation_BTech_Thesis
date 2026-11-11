// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98127268;
  double density_weight = 0.10313998;
  double prefix_weight = 0.49471996;
  double neighborhood_weight = 0.15844431;
  double late_weight = 0.27182168;
  double critical_weight = 0.29279146;
  unsigned budget = 13;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
