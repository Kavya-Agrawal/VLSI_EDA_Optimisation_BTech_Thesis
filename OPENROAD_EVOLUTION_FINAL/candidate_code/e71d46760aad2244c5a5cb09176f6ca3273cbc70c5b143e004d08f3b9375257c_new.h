// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68075305;
  double density_weight = 0.16647621;
  double prefix_weight = 0.02270985;
  double neighborhood_weight = 0.00585257;
  double late_weight = 0.10823498;
  double critical_weight = 0.15312988;
  unsigned budget = 23;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
