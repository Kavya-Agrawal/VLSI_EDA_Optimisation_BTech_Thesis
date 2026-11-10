// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09457057;
  double density_weight = 0.09086203;
  double prefix_weight = 0.09754181;
  double neighborhood_weight = 0.19447403;
  double late_weight = 0.24775621;
  double critical_weight = 0.45006206;
  unsigned budget = 36;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
