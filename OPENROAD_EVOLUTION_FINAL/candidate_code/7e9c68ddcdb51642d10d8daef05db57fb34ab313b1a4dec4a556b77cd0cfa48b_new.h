// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19645274;
  double density_weight = 0.53918134;
  double prefix_weight = 0.16613624;
  double neighborhood_weight = 0.35023892;
  double late_weight = 0.12472565;
  double critical_weight = 0.03530141;
  unsigned budget = 21;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
