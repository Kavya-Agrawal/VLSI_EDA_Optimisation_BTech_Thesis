// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.69822724;
  double density_weight = 0.31636975;
  double prefix_weight = 0.00119028;
  double neighborhood_weight = 0.39858849;
  double late_weight = 0.09475658;
  double critical_weight = 0.16950603;
  unsigned budget = 17;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
