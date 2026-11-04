// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29392377;
  double density_weight = 0.14365567;
  double prefix_weight = 0.14395119;
  double neighborhood_weight = 0.11004789;
  double late_weight = 0.13378657;
  double critical_weight = 0.22958694;
  unsigned budget = 22;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
