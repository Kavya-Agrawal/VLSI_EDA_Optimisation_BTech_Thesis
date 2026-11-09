// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19931729;
  double density_weight = 0.44039831;
  double prefix_weight = 0.25397266;
  double neighborhood_weight = 0.13039824;
  double late_weight = 0.14390939;
  double critical_weight = 0.44293842;
  unsigned budget = 18;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
