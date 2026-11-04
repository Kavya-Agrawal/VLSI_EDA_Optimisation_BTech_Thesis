// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07482757;
  double density_weight = 0.02086832;
  double prefix_weight = 0.24141538;
  double neighborhood_weight = 0.39315734;
  double late_weight = 0.08487326;
  double critical_weight = 0.17104881;
  unsigned budget = 28;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
