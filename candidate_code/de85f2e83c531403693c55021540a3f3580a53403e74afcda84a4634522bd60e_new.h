// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63872534;
  double density_weight = 0.09490906;
  double prefix_weight = 0.37818044;
  double neighborhood_weight = 0.21482860;
  double late_weight = 0.06245774;
  double critical_weight = 0.33059704;
  unsigned budget = 22;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
