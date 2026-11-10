// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01028108;
  double density_weight = 0.31418467;
  double prefix_weight = 0.05255351;
  double neighborhood_weight = 0.19790089;
  double late_weight = 0.16136789;
  double critical_weight = 0.07010903;
  unsigned budget = 40;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
