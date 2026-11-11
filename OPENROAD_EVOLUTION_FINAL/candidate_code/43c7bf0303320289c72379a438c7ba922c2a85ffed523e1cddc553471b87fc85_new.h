// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30600651;
  double density_weight = 0.19331489;
  double prefix_weight = 0.28750852;
  double neighborhood_weight = 0.16823593;
  double late_weight = 0.26092383;
  double critical_weight = 0.05854136;
  unsigned budget = 15;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
