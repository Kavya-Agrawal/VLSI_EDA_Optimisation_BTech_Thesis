// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18665870;
  double density_weight = 0.02657838;
  double prefix_weight = 0.47901252;
  double neighborhood_weight = 0.17301500;
  double late_weight = 0.04235761;
  double critical_weight = 0.45869812;
  unsigned budget = 11;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
