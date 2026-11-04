// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29673870;
  double density_weight = 0.12028927;
  double prefix_weight = 0.05930083;
  double neighborhood_weight = 0.32309782;
  double late_weight = 0.14985877;
  double critical_weight = 0.04900459;
  unsigned budget = 14;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
