// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04336192;
  double density_weight = 0.56619399;
  double prefix_weight = 0.48225840;
  double neighborhood_weight = 0.14396972;
  double late_weight = 0.17009719;
  double critical_weight = 0.03780377;
  unsigned budget = 10;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
