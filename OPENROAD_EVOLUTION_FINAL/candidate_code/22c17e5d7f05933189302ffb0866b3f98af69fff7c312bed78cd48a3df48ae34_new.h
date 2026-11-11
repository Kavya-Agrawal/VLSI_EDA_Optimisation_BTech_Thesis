// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39723000;
  double density_weight = 0.39779082;
  double prefix_weight = 0.47517511;
  double neighborhood_weight = 0.08806043;
  double late_weight = 0.05242085;
  double critical_weight = 0.27124318;
  unsigned budget = 32;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
