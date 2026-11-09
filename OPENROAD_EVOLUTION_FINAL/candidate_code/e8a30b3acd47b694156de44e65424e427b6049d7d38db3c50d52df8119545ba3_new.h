// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44304501;
  double density_weight = 0.21781332;
  double prefix_weight = 0.10810233;
  double neighborhood_weight = 0.00503013;
  double late_weight = 0.19758467;
  double critical_weight = 0.21762416;
  unsigned budget = 19;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
