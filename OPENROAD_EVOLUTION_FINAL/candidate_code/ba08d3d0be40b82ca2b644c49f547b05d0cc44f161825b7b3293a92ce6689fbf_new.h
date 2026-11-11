// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15058746;
  double density_weight = 0.02528446;
  double prefix_weight = 0.09615947;
  double neighborhood_weight = 0.15140457;
  double late_weight = 0.11115792;
  double critical_weight = 0.22221263;
  unsigned budget = 37;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
