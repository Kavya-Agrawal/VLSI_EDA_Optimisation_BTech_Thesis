// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26243053;
  double density_weight = 0.08885224;
  double prefix_weight = 0.17584595;
  double neighborhood_weight = 0.29646953;
  double late_weight = 0.29317327;
  double critical_weight = 0.21811214;
  unsigned budget = 16;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
