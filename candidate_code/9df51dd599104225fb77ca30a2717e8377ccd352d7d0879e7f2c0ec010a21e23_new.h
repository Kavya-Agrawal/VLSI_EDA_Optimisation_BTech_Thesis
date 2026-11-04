// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93811963;
  double density_weight = 0.36454503;
  double prefix_weight = 0.36147497;
  double neighborhood_weight = 0.05670723;
  double late_weight = 0.19715557;
  double critical_weight = 0.02093117;
  unsigned budget = 11;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
