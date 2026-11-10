// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65747020;
  double density_weight = 0.27609516;
  double prefix_weight = 0.36115072;
  double neighborhood_weight = 0.13849047;
  double late_weight = 0.05648279;
  double critical_weight = 0.46450110;
  unsigned budget = 30;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
