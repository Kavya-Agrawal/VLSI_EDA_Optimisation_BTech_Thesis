// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45099095;
  double density_weight = 0.25850409;
  double prefix_weight = 0.34294222;
  double neighborhood_weight = 0.14585715;
  double late_weight = 0.04091338;
  double critical_weight = 0.29158777;
  unsigned budget = 29;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
