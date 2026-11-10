// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54590531;
  double density_weight = 0.45269312;
  double prefix_weight = 0.35197897;
  double neighborhood_weight = 0.16389081;
  double late_weight = 0.26723724;
  double critical_weight = 0.02848324;
  unsigned budget = 8;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
