// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07301856;
  double density_weight = 0.51894766;
  double prefix_weight = 0.27897678;
  double neighborhood_weight = 0.02629964;
  double late_weight = 0.14524761;
  double critical_weight = 0.17480940;
  unsigned budget = 6;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
