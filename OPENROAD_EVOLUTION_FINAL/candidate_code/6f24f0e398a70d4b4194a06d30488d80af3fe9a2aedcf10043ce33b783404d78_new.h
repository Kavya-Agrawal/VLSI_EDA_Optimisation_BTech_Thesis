// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49169061;
  double density_weight = 0.28922013;
  double prefix_weight = 0.17161796;
  double neighborhood_weight = 0.05106617;
  double late_weight = 0.13984773;
  double critical_weight = 0.27306252;
  unsigned budget = 32;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
