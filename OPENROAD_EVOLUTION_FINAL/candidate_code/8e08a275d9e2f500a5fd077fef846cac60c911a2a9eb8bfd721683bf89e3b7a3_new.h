// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33328820;
  double density_weight = 0.06732926;
  double prefix_weight = 0.38809925;
  double neighborhood_weight = 0.12789734;
  double late_weight = 0.17873610;
  double critical_weight = 0.34434335;
  unsigned budget = 38;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
