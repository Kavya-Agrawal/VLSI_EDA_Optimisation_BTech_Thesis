// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59512562;
  double density_weight = 0.19197581;
  double prefix_weight = 0.39938834;
  double neighborhood_weight = 0.03855124;
  double late_weight = 0.28635297;
  double critical_weight = 0.37934621;
  unsigned budget = 12;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
