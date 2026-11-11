// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31383947;
  double density_weight = 0.16646716;
  double prefix_weight = 0.16130418;
  double neighborhood_weight = 0.08655132;
  double late_weight = 0.28836646;
  double critical_weight = 0.43560575;
  unsigned budget = 20;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
