// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21200339;
  double density_weight = 0.34105751;
  double prefix_weight = 0.30739711;
  double neighborhood_weight = 0.16722245;
  double late_weight = 0.14646396;
  double critical_weight = 0.12287658;
  unsigned budget = 33;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
