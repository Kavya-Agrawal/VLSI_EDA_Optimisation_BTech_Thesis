// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17833828;
  double density_weight = 0.32018422;
  double prefix_weight = 0.07465088;
  double neighborhood_weight = 0.36479803;
  double late_weight = 0.12778989;
  double critical_weight = 0.19370132;
  unsigned budget = 23;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
