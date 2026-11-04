// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58255010;
  double density_weight = 0.15779329;
  double prefix_weight = 0.21109982;
  double neighborhood_weight = 0.33499324;
  double late_weight = 0.15199777;
  double critical_weight = 0.14758035;
  unsigned budget = 13;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
