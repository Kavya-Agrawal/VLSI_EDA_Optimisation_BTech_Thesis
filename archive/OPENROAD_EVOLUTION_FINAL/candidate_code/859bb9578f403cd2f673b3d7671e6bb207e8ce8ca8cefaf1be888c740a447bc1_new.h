// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68557953;
  double density_weight = 0.31480486;
  double prefix_weight = 0.21746441;
  double neighborhood_weight = 0.16386753;
  double late_weight = 0.13406325;
  double critical_weight = 0.11442586;
  unsigned budget = 25;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
