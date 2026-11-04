// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64456246;
  double density_weight = 0.34143250;
  double prefix_weight = 0.20243203;
  double neighborhood_weight = 0.16181209;
  double late_weight = 0.07902226;
  double critical_weight = 0.17957170;
  unsigned budget = 35;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
