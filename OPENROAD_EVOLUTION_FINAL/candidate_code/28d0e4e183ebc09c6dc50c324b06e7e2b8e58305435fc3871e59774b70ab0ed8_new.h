// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47221881;
  double density_weight = 0.28726408;
  double prefix_weight = 0.32424766;
  double neighborhood_weight = 0.21932419;
  double late_weight = 0.11511118;
  double critical_weight = 0.31779718;
  unsigned budget = 6;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
