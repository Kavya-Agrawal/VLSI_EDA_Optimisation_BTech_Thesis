// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43718127;
  double density_weight = 0.59013942;
  double prefix_weight = 0.08425577;
  double neighborhood_weight = 0.34296034;
  double late_weight = 0.13261335;
  double critical_weight = 0.31376016;
  unsigned budget = 33;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
