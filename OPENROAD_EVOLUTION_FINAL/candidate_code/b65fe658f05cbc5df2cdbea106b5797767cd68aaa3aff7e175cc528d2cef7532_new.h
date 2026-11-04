// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02621538;
  double density_weight = 0.00581583;
  double prefix_weight = 0.44524640;
  double neighborhood_weight = 0.23444985;
  double late_weight = 0.21741235;
  double critical_weight = 0.19704891;
  unsigned budget = 22;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
