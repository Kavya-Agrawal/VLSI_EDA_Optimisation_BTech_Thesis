// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32116772;
  double density_weight = 0.18558806;
  double prefix_weight = 0.14248780;
  double neighborhood_weight = 0.09672049;
  double late_weight = 0.24531429;
  double critical_weight = 0.20686449;
  unsigned budget = 25;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
