// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79475342;
  double density_weight = 0.09072787;
  double prefix_weight = 0.36493283;
  double neighborhood_weight = 0.10197458;
  double late_weight = 0.04691782;
  double critical_weight = 0.17315076;
  unsigned budget = 7;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
