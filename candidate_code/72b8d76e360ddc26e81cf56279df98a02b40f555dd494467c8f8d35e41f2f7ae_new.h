// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87639199;
  double density_weight = 0.18276827;
  double prefix_weight = 0.04750158;
  double neighborhood_weight = 0.15227136;
  double late_weight = 0.29899960;
  double critical_weight = 0.11162936;
  unsigned budget = 4;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
