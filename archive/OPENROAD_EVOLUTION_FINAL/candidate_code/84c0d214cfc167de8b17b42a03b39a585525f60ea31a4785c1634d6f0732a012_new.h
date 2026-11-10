// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15610781;
  double density_weight = 0.57952559;
  double prefix_weight = 0.24438585;
  double neighborhood_weight = 0.22845626;
  double late_weight = 0.19953836;
  double critical_weight = 0.26775373;
  unsigned budget = 34;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
