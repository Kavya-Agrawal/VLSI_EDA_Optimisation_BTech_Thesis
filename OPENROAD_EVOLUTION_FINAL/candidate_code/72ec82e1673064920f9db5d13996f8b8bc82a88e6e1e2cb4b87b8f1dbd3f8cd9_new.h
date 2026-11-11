// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94771350;
  double density_weight = 0.26871816;
  double prefix_weight = 0.49827579;
  double neighborhood_weight = 0.10330023;
  double late_weight = 0.09730201;
  double critical_weight = 0.39648884;
  unsigned budget = 39;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
