// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86747764;
  double density_weight = 0.45564873;
  double prefix_weight = 0.23335727;
  double neighborhood_weight = 0.38681959;
  double late_weight = 0.23066883;
  double critical_weight = 0.25533006;
  unsigned budget = 18;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
