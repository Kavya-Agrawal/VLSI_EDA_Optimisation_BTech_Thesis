// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99258038;
  double density_weight = 0.52850928;
  double prefix_weight = 0.30686651;
  double neighborhood_weight = 0.23794134;
  double late_weight = 0.03336280;
  double critical_weight = 0.17555499;
  unsigned budget = 31;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
