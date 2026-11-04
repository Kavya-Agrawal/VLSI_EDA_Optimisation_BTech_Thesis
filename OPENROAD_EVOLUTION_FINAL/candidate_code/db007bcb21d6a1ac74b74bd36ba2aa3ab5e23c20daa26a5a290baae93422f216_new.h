// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07185805;
  double density_weight = 0.18586627;
  double prefix_weight = 0.38815834;
  double neighborhood_weight = 0.39032928;
  double late_weight = 0.07011394;
  double critical_weight = 0.06164859;
  unsigned budget = 31;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
