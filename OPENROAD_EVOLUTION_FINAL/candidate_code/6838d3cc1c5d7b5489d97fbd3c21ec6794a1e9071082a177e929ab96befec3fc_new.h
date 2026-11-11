// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34589180;
  double density_weight = 0.03906891;
  double prefix_weight = 0.13929064;
  double neighborhood_weight = 0.03209751;
  double late_weight = 0.29539712;
  double critical_weight = 0.19066136;
  unsigned budget = 27;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
