// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76539960;
  double density_weight = 0.44158530;
  double prefix_weight = 0.14766702;
  double neighborhood_weight = 0.09022789;
  double late_weight = 0.06149269;
  double critical_weight = 0.21512787;
  unsigned budget = 7;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
