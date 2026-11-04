// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93390545;
  double density_weight = 0.54673607;
  double prefix_weight = 0.32621545;
  double neighborhood_weight = 0.21211789;
  double late_weight = 0.17989385;
  double critical_weight = 0.23794589;
  unsigned budget = 8;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
