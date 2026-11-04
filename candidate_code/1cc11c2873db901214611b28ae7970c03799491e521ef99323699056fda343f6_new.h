// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01169367;
  double density_weight = 0.29044513;
  double prefix_weight = 0.44518313;
  double neighborhood_weight = 0.37774313;
  double late_weight = 0.04824737;
  double critical_weight = 0.21485731;
  unsigned budget = 7;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
