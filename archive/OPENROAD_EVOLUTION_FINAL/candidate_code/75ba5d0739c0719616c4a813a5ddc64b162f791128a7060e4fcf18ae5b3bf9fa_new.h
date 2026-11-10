// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43782160;
  double density_weight = 0.24665671;
  double prefix_weight = 0.42541921;
  double neighborhood_weight = 0.21884260;
  double late_weight = 0.10712660;
  double critical_weight = 0.26910957;
  unsigned budget = 25;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
