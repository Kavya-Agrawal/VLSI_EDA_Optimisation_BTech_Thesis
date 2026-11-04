// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57257595;
  double density_weight = 0.44308096;
  double prefix_weight = 0.19058926;
  double neighborhood_weight = 0.00539100;
  double late_weight = 0.27325094;
  double critical_weight = 0.19937354;
  unsigned budget = 15;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
