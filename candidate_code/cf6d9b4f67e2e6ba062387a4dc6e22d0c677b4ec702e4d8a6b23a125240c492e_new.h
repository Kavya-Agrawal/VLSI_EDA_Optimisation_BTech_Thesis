// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56278294;
  double density_weight = 0.24505051;
  double prefix_weight = 0.18767347;
  double neighborhood_weight = 0.19414368;
  double late_weight = 0.05767225;
  double critical_weight = 0.46756073;
  unsigned budget = 4;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
