// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94220544;
  double density_weight = 0.11973936;
  double prefix_weight = 0.42800655;
  double neighborhood_weight = 0.29431031;
  double late_weight = 0.28338262;
  double critical_weight = 0.32143010;
  unsigned budget = 9;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
