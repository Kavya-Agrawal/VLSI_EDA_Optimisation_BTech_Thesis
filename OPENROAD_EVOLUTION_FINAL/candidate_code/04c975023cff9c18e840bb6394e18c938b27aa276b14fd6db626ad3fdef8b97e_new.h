// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50567058;
  double density_weight = 0.42207810;
  double prefix_weight = 0.38218737;
  double neighborhood_weight = 0.31149459;
  double late_weight = 0.04115045;
  double critical_weight = 0.33576673;
  unsigned budget = 19;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
