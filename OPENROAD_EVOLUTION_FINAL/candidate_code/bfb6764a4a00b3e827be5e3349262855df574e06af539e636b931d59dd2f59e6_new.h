// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81985242;
  double density_weight = 0.46048540;
  double prefix_weight = 0.06058097;
  double neighborhood_weight = 0.03996269;
  double late_weight = 0.07630754;
  double critical_weight = 0.07987492;
  unsigned budget = 26;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
