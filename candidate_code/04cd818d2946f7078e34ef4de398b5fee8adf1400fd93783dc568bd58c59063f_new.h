// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98468369;
  double density_weight = 0.46336517;
  double prefix_weight = 0.25240853;
  double neighborhood_weight = 0.28137614;
  double late_weight = 0.12370874;
  double critical_weight = 0.28662506;
  unsigned budget = 31;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
