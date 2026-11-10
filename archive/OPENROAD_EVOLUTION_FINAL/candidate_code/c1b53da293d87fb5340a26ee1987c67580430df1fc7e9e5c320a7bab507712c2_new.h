// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92718738;
  double density_weight = 0.29319375;
  double prefix_weight = 0.35571505;
  double neighborhood_weight = 0.36954609;
  double late_weight = 0.22992911;
  double critical_weight = 0.22315778;
  unsigned budget = 18;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
