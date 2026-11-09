// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08526593;
  double density_weight = 0.18202675;
  double prefix_weight = 0.46192245;
  double neighborhood_weight = 0.37354895;
  double late_weight = 0.10850153;
  double critical_weight = 0.34532787;
  unsigned budget = 39;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
