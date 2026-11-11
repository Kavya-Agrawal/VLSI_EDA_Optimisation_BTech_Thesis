// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09800180;
  double density_weight = 0.41341983;
  double prefix_weight = 0.15535794;
  double neighborhood_weight = 0.27426291;
  double late_weight = 0.05483936;
  double critical_weight = 0.32229839;
  unsigned budget = 37;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
