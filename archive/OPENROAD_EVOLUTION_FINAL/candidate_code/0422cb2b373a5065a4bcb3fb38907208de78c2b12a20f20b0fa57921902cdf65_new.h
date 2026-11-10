// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64685117;
  double density_weight = 0.18330555;
  double prefix_weight = 0.47325927;
  double neighborhood_weight = 0.38011585;
  double late_weight = 0.04609787;
  double critical_weight = 0.20050919;
  unsigned budget = 17;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
