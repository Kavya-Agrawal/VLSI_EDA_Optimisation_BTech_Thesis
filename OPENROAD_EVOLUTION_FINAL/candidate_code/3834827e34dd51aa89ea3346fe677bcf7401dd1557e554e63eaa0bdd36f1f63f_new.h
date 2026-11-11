// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12919856;
  double density_weight = 0.38900508;
  double prefix_weight = 0.09916484;
  double neighborhood_weight = 0.33112555;
  double late_weight = 0.21916397;
  double critical_weight = 0.01976535;
  unsigned budget = 18;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
