// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04234849;
  double density_weight = 0.20387894;
  double prefix_weight = 0.14332979;
  double neighborhood_weight = 0.37175189;
  double late_weight = 0.22712267;
  double critical_weight = 0.48821170;
  unsigned budget = 12;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
