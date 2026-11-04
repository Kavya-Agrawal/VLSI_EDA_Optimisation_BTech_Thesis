// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60926955;
  double density_weight = 0.19930796;
  double prefix_weight = 0.23028339;
  double neighborhood_weight = 0.35378398;
  double late_weight = 0.06678207;
  double critical_weight = 0.40229569;
  unsigned budget = 28;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
