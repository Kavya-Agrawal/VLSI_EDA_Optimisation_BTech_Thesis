// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90209097;
  double density_weight = 0.56333782;
  double prefix_weight = 0.12684192;
  double neighborhood_weight = 0.35950567;
  double late_weight = 0.21829819;
  double critical_weight = 0.08497228;
  unsigned budget = 25;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
