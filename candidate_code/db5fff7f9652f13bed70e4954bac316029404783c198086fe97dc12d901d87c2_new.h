// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14919861;
  double density_weight = 0.51771675;
  double prefix_weight = 0.32888477;
  double neighborhood_weight = 0.00641296;
  double late_weight = 0.02708419;
  double critical_weight = 0.25563577;
  unsigned budget = 27;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
