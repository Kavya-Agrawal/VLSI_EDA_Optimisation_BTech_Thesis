// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55806579;
  double density_weight = 0.24616792;
  double prefix_weight = 0.19900755;
  double neighborhood_weight = 0.07476307;
  double late_weight = 0.28032711;
  double critical_weight = 0.48795020;
  unsigned budget = 30;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
