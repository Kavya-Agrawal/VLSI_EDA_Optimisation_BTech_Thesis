// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07017285;
  double density_weight = 0.27046783;
  double prefix_weight = 0.09353477;
  double neighborhood_weight = 0.28526830;
  double late_weight = 0.22965601;
  double critical_weight = 0.33210100;
  unsigned budget = 15;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
