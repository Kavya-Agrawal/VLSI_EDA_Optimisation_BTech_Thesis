// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94362778;
  double density_weight = 0.39997360;
  double prefix_weight = 0.40690389;
  double neighborhood_weight = 0.37231334;
  double late_weight = 0.17063586;
  double critical_weight = 0.11890866;
  unsigned budget = 37;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
