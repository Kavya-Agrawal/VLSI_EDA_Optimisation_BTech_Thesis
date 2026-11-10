// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09138479;
  double density_weight = 0.15519290;
  double prefix_weight = 0.07321242;
  double neighborhood_weight = 0.03868158;
  double late_weight = 0.07368710;
  double critical_weight = 0.23919514;
  unsigned budget = 9;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
