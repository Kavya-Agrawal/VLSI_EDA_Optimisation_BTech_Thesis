// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67832519;
  double density_weight = 0.55979276;
  double prefix_weight = 0.04938945;
  double neighborhood_weight = 0.02275398;
  double late_weight = 0.14884586;
  double critical_weight = 0.39821697;
  unsigned budget = 12;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
