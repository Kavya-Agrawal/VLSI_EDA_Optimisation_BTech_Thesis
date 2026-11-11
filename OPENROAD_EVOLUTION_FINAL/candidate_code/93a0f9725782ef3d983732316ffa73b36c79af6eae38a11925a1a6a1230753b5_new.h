// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85195756;
  double density_weight = 0.29377127;
  double prefix_weight = 0.02524257;
  double neighborhood_weight = 0.11498395;
  double late_weight = 0.20156475;
  double critical_weight = 0.37669650;
  unsigned budget = 21;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
