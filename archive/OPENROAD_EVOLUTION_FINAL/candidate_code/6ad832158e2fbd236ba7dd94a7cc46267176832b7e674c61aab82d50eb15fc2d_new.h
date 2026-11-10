// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74291951;
  double density_weight = 0.21260228;
  double prefix_weight = 0.46690710;
  double neighborhood_weight = 0.24834980;
  double late_weight = 0.11796978;
  double critical_weight = 0.31207406;
  unsigned budget = 10;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
