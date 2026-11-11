// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07236659;
  double density_weight = 0.48948848;
  double prefix_weight = 0.37411014;
  double neighborhood_weight = 0.19106348;
  double late_weight = 0.00806167;
  double critical_weight = 0.04107330;
  unsigned budget = 15;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
