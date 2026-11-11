// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15105847;
  double density_weight = 0.14853900;
  double prefix_weight = 0.42071716;
  double neighborhood_weight = 0.35208014;
  double late_weight = 0.00263506;
  double critical_weight = 0.09189351;
  unsigned budget = 32;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
