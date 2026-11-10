// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83514554;
  double density_weight = 0.13361208;
  double prefix_weight = 0.38275545;
  double neighborhood_weight = 0.39069545;
  double late_weight = 0.14462816;
  double critical_weight = 0.44910291;
  unsigned budget = 37;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
