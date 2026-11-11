// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54703732;
  double density_weight = 0.29201982;
  double prefix_weight = 0.32454795;
  double neighborhood_weight = 0.08198379;
  double late_weight = 0.22079378;
  double critical_weight = 0.38249674;
  unsigned budget = 15;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
