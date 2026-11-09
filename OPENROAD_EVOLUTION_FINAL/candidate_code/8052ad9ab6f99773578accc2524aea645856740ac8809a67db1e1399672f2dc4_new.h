// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87701654;
  double density_weight = 0.01248265;
  double prefix_weight = 0.10577637;
  double neighborhood_weight = 0.24349514;
  double late_weight = 0.13647374;
  double critical_weight = 0.43939333;
  unsigned budget = 26;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
