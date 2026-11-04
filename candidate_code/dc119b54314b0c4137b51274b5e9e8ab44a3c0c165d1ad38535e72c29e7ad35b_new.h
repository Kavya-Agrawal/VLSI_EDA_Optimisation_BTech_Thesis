// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64569683;
  double density_weight = 0.41672941;
  double prefix_weight = 0.48127581;
  double neighborhood_weight = 0.15566208;
  double late_weight = 0.07556517;
  double critical_weight = 0.45711211;
  unsigned budget = 15;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
