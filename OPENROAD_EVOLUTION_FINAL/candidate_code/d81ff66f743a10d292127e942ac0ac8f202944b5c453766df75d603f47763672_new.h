// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43045615;
  double density_weight = 0.37959758;
  double prefix_weight = 0.06422569;
  double neighborhood_weight = 0.19485926;
  double late_weight = 0.18039230;
  double critical_weight = 0.02007575;
  unsigned budget = 5;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
