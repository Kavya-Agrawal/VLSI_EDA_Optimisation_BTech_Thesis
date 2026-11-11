// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62718030;
  double density_weight = 0.56340004;
  double prefix_weight = 0.29871033;
  double neighborhood_weight = 0.21118728;
  double late_weight = 0.07356678;
  double critical_weight = 0.20193634;
  unsigned budget = 15;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
