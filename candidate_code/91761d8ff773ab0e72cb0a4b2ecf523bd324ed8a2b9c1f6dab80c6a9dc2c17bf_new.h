// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74393994;
  double density_weight = 0.29872280;
  double prefix_weight = 0.04188024;
  double neighborhood_weight = 0.34247493;
  double late_weight = 0.15537442;
  double critical_weight = 0.33741594;
  unsigned budget = 15;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
