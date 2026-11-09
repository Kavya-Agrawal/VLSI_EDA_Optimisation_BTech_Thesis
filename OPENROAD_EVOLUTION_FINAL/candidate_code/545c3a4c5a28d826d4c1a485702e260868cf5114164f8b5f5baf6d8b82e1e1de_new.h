// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99862843;
  double density_weight = 0.49226474;
  double prefix_weight = 0.23982780;
  double neighborhood_weight = 0.24090452;
  double late_weight = 0.00576473;
  double critical_weight = 0.41047786;
  unsigned budget = 26;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
