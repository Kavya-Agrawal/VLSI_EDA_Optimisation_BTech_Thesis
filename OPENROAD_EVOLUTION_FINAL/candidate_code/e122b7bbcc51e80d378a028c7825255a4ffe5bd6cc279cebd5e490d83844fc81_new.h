// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23593437;
  double density_weight = 0.40196733;
  double prefix_weight = 0.49944896;
  double neighborhood_weight = 0.19715919;
  double late_weight = 0.18345743;
  double critical_weight = 0.18131060;
  unsigned budget = 12;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
