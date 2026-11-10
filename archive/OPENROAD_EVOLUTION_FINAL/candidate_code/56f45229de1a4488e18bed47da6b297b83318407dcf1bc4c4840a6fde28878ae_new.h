// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13225489;
  double density_weight = 0.51439513;
  double prefix_weight = 0.26151195;
  double neighborhood_weight = 0.22915794;
  double late_weight = 0.02077587;
  double critical_weight = 0.14001629;
  unsigned budget = 19;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
