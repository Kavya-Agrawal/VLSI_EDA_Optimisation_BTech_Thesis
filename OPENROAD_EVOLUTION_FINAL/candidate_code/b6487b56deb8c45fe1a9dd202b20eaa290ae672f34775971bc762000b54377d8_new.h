// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.69635300;
  double density_weight = 0.00287431;
  double prefix_weight = 0.38751954;
  double neighborhood_weight = 0.11586419;
  double late_weight = 0.07154422;
  double critical_weight = 0.11180582;
  unsigned budget = 24;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
