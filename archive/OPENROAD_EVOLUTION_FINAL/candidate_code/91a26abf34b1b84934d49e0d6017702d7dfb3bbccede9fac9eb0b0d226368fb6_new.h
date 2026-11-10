// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93630307;
  double density_weight = 0.35256042;
  double prefix_weight = 0.46907307;
  double neighborhood_weight = 0.02186166;
  double late_weight = 0.03863108;
  double critical_weight = 0.29453422;
  unsigned budget = 34;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
