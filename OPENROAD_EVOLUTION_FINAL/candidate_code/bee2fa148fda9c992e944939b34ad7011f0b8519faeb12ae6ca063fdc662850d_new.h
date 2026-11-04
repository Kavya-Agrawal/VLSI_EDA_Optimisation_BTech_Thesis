// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48916725;
  double density_weight = 0.39734542;
  double prefix_weight = 0.36492164;
  double neighborhood_weight = 0.36207933;
  double late_weight = 0.14269850;
  double critical_weight = 0.02325208;
  unsigned budget = 18;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
