// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43687624;
  double density_weight = 0.20253937;
  double prefix_weight = 0.25162275;
  double neighborhood_weight = 0.21040922;
  double late_weight = 0.02940404;
  double critical_weight = 0.49597495;
  unsigned budget = 11;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
