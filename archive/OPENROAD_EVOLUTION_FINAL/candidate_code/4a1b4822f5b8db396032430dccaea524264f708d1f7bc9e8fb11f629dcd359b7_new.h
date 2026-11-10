// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89536307;
  double density_weight = 0.59261335;
  double prefix_weight = 0.40329815;
  double neighborhood_weight = 0.22759037;
  double late_weight = 0.29091175;
  double critical_weight = 0.09301255;
  unsigned budget = 8;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
