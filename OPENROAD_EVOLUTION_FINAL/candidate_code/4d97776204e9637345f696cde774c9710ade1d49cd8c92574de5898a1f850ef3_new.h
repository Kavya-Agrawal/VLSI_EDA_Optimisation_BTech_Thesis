// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27914117;
  double density_weight = 0.09930054;
  double prefix_weight = 0.21831035;
  double neighborhood_weight = 0.05662049;
  double late_weight = 0.00155302;
  double critical_weight = 0.19986297;
  unsigned budget = 17;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
