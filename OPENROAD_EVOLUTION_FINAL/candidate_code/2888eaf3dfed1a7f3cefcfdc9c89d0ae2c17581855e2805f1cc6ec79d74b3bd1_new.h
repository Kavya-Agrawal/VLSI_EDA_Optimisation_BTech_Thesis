// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05877539;
  double density_weight = 0.55336696;
  double prefix_weight = 0.36386058;
  double neighborhood_weight = 0.37510841;
  double late_weight = 0.25896389;
  double critical_weight = 0.30029479;
  unsigned budget = 31;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
