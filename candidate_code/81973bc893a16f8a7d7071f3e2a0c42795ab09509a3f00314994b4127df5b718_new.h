// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25672106;
  double density_weight = 0.57346091;
  double prefix_weight = 0.29277575;
  double neighborhood_weight = 0.23750313;
  double late_weight = 0.01082093;
  double critical_weight = 0.10847888;
  unsigned budget = 8;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
