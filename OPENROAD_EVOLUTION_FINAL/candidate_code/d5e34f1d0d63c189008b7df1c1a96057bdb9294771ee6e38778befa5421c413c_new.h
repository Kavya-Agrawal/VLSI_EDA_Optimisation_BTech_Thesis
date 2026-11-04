// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99336316;
  double density_weight = 0.26015320;
  double prefix_weight = 0.13324098;
  double neighborhood_weight = 0.30075316;
  double late_weight = 0.06151090;
  double critical_weight = 0.21920854;
  unsigned budget = 16;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
