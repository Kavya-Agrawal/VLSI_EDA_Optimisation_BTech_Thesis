// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75546700;
  double density_weight = 0.11324558;
  double prefix_weight = 0.16987108;
  double neighborhood_weight = 0.09500999;
  double late_weight = 0.11945657;
  double critical_weight = 0.24999316;
  unsigned budget = 15;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
