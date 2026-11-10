// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27749116;
  double density_weight = 0.07155064;
  double prefix_weight = 0.42249321;
  double neighborhood_weight = 0.17879523;
  double late_weight = 0.23260880;
  double critical_weight = 0.17659169;
  unsigned budget = 4;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
