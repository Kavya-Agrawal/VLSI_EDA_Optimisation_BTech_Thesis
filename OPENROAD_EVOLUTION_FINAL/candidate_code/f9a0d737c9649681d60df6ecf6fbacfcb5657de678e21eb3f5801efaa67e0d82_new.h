// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53666265;
  double density_weight = 0.55456522;
  double prefix_weight = 0.00671803;
  double neighborhood_weight = 0.36044821;
  double late_weight = 0.08874387;
  double critical_weight = 0.37578100;
  unsigned budget = 27;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
