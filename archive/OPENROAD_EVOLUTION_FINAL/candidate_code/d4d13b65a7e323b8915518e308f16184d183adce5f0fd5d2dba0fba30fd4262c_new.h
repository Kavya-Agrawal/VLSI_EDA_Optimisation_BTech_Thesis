// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38899442;
  double density_weight = 0.27567016;
  double prefix_weight = 0.01980326;
  double neighborhood_weight = 0.31480453;
  double late_weight = 0.00924907;
  double critical_weight = 0.43152954;
  unsigned budget = 17;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
