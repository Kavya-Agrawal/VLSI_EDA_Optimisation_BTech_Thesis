// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17948267;
  double density_weight = 0.00996779;
  double prefix_weight = 0.49685696;
  double neighborhood_weight = 0.30221971;
  double late_weight = 0.03479811;
  double critical_weight = 0.18189534;
  unsigned budget = 37;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
