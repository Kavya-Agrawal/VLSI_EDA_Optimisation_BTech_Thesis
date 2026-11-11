// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83245237;
  double density_weight = 0.27330032;
  double prefix_weight = 0.18063857;
  double neighborhood_weight = 0.21003962;
  double late_weight = 0.03833627;
  double critical_weight = 0.39288437;
  unsigned budget = 6;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
