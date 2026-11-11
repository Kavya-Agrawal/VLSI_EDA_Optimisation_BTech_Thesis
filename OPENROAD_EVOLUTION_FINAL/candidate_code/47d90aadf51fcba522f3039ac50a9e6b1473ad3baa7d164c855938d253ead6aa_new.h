// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42935065;
  double density_weight = 0.16351500;
  double prefix_weight = 0.43947363;
  double neighborhood_weight = 0.13999470;
  double late_weight = 0.10329910;
  double critical_weight = 0.34304563;
  unsigned budget = 35;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
