// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30894756;
  double density_weight = 0.54355494;
  double prefix_weight = 0.14680250;
  double neighborhood_weight = 0.39506952;
  double late_weight = 0.25013778;
  double critical_weight = 0.44243386;
  unsigned budget = 14;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
