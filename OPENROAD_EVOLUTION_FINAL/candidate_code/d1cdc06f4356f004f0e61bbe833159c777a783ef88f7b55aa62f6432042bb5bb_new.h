// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75832976;
  double density_weight = 0.38686926;
  double prefix_weight = 0.44995191;
  double neighborhood_weight = 0.02039010;
  double late_weight = 0.11061944;
  double critical_weight = 0.07323916;
  unsigned budget = 32;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
