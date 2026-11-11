// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45319484;
  double density_weight = 0.49548364;
  double prefix_weight = 0.44280094;
  double neighborhood_weight = 0.25226856;
  double late_weight = 0.05938318;
  double critical_weight = 0.05859551;
  unsigned budget = 16;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
