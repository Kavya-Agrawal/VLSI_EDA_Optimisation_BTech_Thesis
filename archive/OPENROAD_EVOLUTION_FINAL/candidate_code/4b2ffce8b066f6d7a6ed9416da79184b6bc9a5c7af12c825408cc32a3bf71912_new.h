// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85601322;
  double density_weight = 0.35724523;
  double prefix_weight = 0.44728363;
  double neighborhood_weight = 0.14181055;
  double late_weight = 0.27664641;
  double critical_weight = 0.28285176;
  unsigned budget = 22;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
