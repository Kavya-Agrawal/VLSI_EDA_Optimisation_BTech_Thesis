// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83225508;
  double density_weight = 0.54848676;
  double prefix_weight = 0.46800447;
  double neighborhood_weight = 0.15806879;
  double late_weight = 0.02068098;
  double critical_weight = 0.08856117;
  unsigned budget = 38;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
