// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77893810;
  double density_weight = 0.03095594;
  double prefix_weight = 0.44245831;
  double neighborhood_weight = 0.25438434;
  double late_weight = 0.20685157;
  double critical_weight = 0.37780259;
  unsigned budget = 15;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
