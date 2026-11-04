// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79145328;
  double density_weight = 0.46336497;
  double prefix_weight = 0.37877252;
  double neighborhood_weight = 0.23486697;
  double late_weight = 0.29881961;
  double critical_weight = 0.11332335;
  unsigned budget = 10;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
