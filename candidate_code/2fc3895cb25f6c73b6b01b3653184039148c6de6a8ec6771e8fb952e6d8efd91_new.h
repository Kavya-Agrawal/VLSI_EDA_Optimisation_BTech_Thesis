// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55252404;
  double density_weight = 0.55128354;
  double prefix_weight = 0.35242017;
  double neighborhood_weight = 0.00619567;
  double late_weight = 0.20786124;
  double critical_weight = 0.19861394;
  unsigned budget = 28;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
