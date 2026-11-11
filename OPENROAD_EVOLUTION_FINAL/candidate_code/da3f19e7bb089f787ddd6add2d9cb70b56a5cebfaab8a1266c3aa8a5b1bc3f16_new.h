// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90159489;
  double density_weight = 0.57600115;
  double prefix_weight = 0.19430916;
  double neighborhood_weight = 0.24504311;
  double late_weight = 0.12166816;
  double critical_weight = 0.31145999;
  unsigned budget = 10;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
