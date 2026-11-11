// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34935455;
  double density_weight = 0.47193819;
  double prefix_weight = 0.28902304;
  double neighborhood_weight = 0.24974569;
  double late_weight = 0.03846301;
  double critical_weight = 0.43455210;
  unsigned budget = 27;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
