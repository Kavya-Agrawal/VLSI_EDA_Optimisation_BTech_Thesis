// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29269408;
  double density_weight = 0.15950277;
  double prefix_weight = 0.38850752;
  double neighborhood_weight = 0.23595188;
  double late_weight = 0.18297739;
  double critical_weight = 0.12761910;
  unsigned budget = 39;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
