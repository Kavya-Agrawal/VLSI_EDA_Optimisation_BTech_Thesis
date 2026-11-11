// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44815553;
  double density_weight = 0.02760865;
  double prefix_weight = 0.41592353;
  double neighborhood_weight = 0.07141388;
  double late_weight = 0.06249676;
  double critical_weight = 0.29318627;
  unsigned budget = 28;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
