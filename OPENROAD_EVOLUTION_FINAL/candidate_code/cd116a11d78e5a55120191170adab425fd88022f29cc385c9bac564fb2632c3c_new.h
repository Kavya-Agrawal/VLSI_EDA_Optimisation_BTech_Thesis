// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36131614;
  double density_weight = 0.33884253;
  double prefix_weight = 0.07101101;
  double neighborhood_weight = 0.20521711;
  double late_weight = 0.20274704;
  double critical_weight = 0.06402041;
  unsigned budget = 6;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
