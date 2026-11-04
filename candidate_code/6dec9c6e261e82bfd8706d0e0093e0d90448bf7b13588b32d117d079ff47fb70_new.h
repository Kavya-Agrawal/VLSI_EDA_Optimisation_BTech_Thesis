// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22924120;
  double density_weight = 0.54534413;
  double prefix_weight = 0.01863082;
  double neighborhood_weight = 0.38433759;
  double late_weight = 0.07772917;
  double critical_weight = 0.33757160;
  unsigned budget = 10;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
