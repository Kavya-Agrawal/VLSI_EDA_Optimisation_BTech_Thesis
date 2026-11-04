// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22393507;
  double density_weight = 0.25968291;
  double prefix_weight = 0.45015361;
  double neighborhood_weight = 0.00039555;
  double late_weight = 0.15175643;
  double critical_weight = 0.14776024;
  unsigned budget = 29;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
