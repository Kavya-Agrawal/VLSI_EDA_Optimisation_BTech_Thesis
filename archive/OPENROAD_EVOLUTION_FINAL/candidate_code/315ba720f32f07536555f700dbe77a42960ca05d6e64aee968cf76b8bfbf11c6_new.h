// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49495490;
  double density_weight = 0.04554291;
  double prefix_weight = 0.22341337;
  double neighborhood_weight = 0.17376495;
  double late_weight = 0.21499017;
  double critical_weight = 0.02776012;
  unsigned budget = 9;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
