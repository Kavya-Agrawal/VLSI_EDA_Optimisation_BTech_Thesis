// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15592297;
  double density_weight = 0.20646249;
  double prefix_weight = 0.32271386;
  double neighborhood_weight = 0.11554650;
  double late_weight = 0.01843909;
  double critical_weight = 0.35174590;
  unsigned budget = 8;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
