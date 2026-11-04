// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94280825;
  double density_weight = 0.58720572;
  double prefix_weight = 0.26734788;
  double neighborhood_weight = 0.27603188;
  double late_weight = 0.20346268;
  double critical_weight = 0.41939722;
  unsigned budget = 27;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
