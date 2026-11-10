// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30170633;
  double density_weight = 0.47106142;
  double prefix_weight = 0.49945173;
  double neighborhood_weight = 0.19531229;
  double late_weight = 0.21808377;
  double critical_weight = 0.16685560;
  unsigned budget = 32;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
