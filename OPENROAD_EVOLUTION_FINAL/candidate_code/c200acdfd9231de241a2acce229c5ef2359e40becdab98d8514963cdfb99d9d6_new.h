// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83172153;
  double density_weight = 0.52014134;
  double prefix_weight = 0.14923099;
  double neighborhood_weight = 0.35844205;
  double late_weight = 0.29365731;
  double critical_weight = 0.19107568;
  unsigned budget = 8;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
