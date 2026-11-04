// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72407490;
  double density_weight = 0.14082185;
  double prefix_weight = 0.30671705;
  double neighborhood_weight = 0.06225880;
  double late_weight = 0.09373239;
  double critical_weight = 0.07041994;
  unsigned budget = 20;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
