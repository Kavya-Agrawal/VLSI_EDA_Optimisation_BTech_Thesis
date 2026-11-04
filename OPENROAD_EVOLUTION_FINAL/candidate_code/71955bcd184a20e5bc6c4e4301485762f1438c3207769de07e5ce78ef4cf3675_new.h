// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52106939;
  double density_weight = 0.50209659;
  double prefix_weight = 0.14766683;
  double neighborhood_weight = 0.17526415;
  double late_weight = 0.02922293;
  double critical_weight = 0.10520566;
  unsigned budget = 7;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
