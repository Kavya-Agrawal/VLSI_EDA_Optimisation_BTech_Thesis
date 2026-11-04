// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92992907;
  double density_weight = 0.36959826;
  double prefix_weight = 0.47525910;
  double neighborhood_weight = 0.05442701;
  double late_weight = 0.14140388;
  double critical_weight = 0.08107134;
  unsigned budget = 29;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
