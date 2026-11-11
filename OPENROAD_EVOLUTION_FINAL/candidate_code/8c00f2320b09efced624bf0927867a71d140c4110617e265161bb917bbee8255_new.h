// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43619357;
  double density_weight = 0.01404149;
  double prefix_weight = 0.06894862;
  double neighborhood_weight = 0.22914334;
  double late_weight = 0.28923424;
  double critical_weight = 0.31650992;
  unsigned budget = 28;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
