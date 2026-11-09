// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97539488;
  double density_weight = 0.10077894;
  double prefix_weight = 0.32769775;
  double neighborhood_weight = 0.36008708;
  double late_weight = 0.04476454;
  double critical_weight = 0.33190422;
  unsigned budget = 27;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
