// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34211530;
  double density_weight = 0.05704788;
  double prefix_weight = 0.37850109;
  double neighborhood_weight = 0.00132781;
  double late_weight = 0.09414307;
  double critical_weight = 0.15776180;
  unsigned budget = 9;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
