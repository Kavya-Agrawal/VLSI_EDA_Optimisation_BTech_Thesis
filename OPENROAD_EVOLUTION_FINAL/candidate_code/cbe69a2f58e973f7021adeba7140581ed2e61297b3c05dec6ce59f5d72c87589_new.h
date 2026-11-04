// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09255054;
  double density_weight = 0.37431375;
  double prefix_weight = 0.15671899;
  double neighborhood_weight = 0.26193882;
  double late_weight = 0.17730511;
  double critical_weight = 0.35705039;
  unsigned budget = 21;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
