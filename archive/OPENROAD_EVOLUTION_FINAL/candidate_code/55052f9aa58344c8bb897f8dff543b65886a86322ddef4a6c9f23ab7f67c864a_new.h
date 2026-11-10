// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25384782;
  double density_weight = 0.49271405;
  double prefix_weight = 0.17742202;
  double neighborhood_weight = 0.11327713;
  double late_weight = 0.04149932;
  double critical_weight = 0.42495197;
  unsigned budget = 10;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
