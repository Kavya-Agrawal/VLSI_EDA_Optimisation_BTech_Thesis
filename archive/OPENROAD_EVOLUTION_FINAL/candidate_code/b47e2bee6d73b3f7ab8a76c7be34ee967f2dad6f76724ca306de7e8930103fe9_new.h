// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38583043;
  double density_weight = 0.13850425;
  double prefix_weight = 0.04356459;
  double neighborhood_weight = 0.37340891;
  double late_weight = 0.04532182;
  double critical_weight = 0.28310118;
  unsigned budget = 20;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
