// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83914723;
  double density_weight = 0.58296115;
  double prefix_weight = 0.37161387;
  double neighborhood_weight = 0.24312338;
  double late_weight = 0.29493893;
  double critical_weight = 0.25183371;
  unsigned budget = 32;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
