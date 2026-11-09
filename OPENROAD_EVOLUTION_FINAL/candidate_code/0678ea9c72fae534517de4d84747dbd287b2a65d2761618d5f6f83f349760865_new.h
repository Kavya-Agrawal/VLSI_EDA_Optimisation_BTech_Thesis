// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09957663;
  double density_weight = 0.05726139;
  double prefix_weight = 0.11417649;
  double neighborhood_weight = 0.32654204;
  double late_weight = 0.08788213;
  double critical_weight = 0.41407287;
  unsigned budget = 27;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
