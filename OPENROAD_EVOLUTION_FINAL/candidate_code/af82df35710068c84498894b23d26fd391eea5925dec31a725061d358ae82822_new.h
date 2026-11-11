// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09590912;
  double density_weight = 0.59292328;
  double prefix_weight = 0.01454687;
  double neighborhood_weight = 0.27733032;
  double late_weight = 0.24181230;
  double critical_weight = 0.05205997;
  unsigned budget = 25;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
