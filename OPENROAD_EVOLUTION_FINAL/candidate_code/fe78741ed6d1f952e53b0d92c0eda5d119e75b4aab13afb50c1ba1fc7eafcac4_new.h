// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60849944;
  double density_weight = 0.44388742;
  double prefix_weight = 0.47965688;
  double neighborhood_weight = 0.01404140;
  double late_weight = 0.00245609;
  double critical_weight = 0.06146711;
  unsigned budget = 36;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
