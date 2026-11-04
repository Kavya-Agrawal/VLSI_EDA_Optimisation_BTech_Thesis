// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20427340;
  double density_weight = 0.33039222;
  double prefix_weight = 0.17199144;
  double neighborhood_weight = 0.13696886;
  double late_weight = 0.22980191;
  double critical_weight = 0.43168992;
  unsigned budget = 37;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
