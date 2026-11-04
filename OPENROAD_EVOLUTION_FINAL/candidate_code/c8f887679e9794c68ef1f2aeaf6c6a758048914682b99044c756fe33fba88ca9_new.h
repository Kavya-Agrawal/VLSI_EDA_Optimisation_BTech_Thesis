// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09457348;
  double density_weight = 0.07022779;
  double prefix_weight = 0.02165433;
  double neighborhood_weight = 0.15031890;
  double late_weight = 0.03554033;
  double critical_weight = 0.35358289;
  unsigned budget = 17;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
