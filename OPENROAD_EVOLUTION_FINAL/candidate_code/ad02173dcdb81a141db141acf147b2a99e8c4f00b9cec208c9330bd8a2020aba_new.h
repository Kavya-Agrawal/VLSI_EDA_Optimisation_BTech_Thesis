// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33212854;
  double density_weight = 0.48706856;
  double prefix_weight = 0.06433870;
  double neighborhood_weight = 0.27259874;
  double late_weight = 0.13312829;
  double critical_weight = 0.16833336;
  unsigned budget = 16;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
