// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20895681;
  double density_weight = 0.20175545;
  double prefix_weight = 0.49145352;
  double neighborhood_weight = 0.39566403;
  double late_weight = 0.29607396;
  double critical_weight = 0.23566999;
  unsigned budget = 10;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
