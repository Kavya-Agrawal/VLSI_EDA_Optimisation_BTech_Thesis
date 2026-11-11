// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56826016;
  double density_weight = 0.19905382;
  double prefix_weight = 0.37954009;
  double neighborhood_weight = 0.10329721;
  double late_weight = 0.27968563;
  double critical_weight = 0.34252163;
  unsigned budget = 20;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
