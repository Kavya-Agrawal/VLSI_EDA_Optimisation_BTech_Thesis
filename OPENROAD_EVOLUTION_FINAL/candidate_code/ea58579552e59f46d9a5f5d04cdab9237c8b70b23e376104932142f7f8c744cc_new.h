// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32217266;
  double density_weight = 0.54053206;
  double prefix_weight = 0.08079824;
  double neighborhood_weight = 0.03281452;
  double late_weight = 0.07458627;
  double critical_weight = 0.09819944;
  unsigned budget = 18;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
