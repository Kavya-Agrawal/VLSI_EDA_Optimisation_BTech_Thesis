// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60091202;
  double density_weight = 0.48157601;
  double prefix_weight = 0.36773257;
  double neighborhood_weight = 0.20465273;
  double late_weight = 0.27636170;
  double critical_weight = 0.32524748;
  unsigned budget = 33;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
