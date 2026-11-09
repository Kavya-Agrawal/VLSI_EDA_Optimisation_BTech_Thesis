// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32446753;
  double density_weight = 0.41688568;
  double prefix_weight = 0.29546042;
  double neighborhood_weight = 0.00744652;
  double late_weight = 0.08936245;
  double critical_weight = 0.42095708;
  unsigned budget = 38;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
