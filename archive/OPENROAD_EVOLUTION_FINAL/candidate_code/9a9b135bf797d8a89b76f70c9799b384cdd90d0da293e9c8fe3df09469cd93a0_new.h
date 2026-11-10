// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71423583;
  double density_weight = 0.54052489;
  double prefix_weight = 0.42953021;
  double neighborhood_weight = 0.00164285;
  double late_weight = 0.21003949;
  double critical_weight = 0.13251239;
  unsigned budget = 20;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
