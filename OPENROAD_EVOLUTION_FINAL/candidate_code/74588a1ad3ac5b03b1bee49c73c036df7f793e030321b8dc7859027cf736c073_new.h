// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55093598;
  double density_weight = 0.19230961;
  double prefix_weight = 0.07792854;
  double neighborhood_weight = 0.38589177;
  double late_weight = 0.02754629;
  double critical_weight = 0.45588625;
  unsigned budget = 33;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
