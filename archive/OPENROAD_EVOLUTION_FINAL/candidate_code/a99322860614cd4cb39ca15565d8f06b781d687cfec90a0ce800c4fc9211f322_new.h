// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60134997;
  double density_weight = 0.16268167;
  double prefix_weight = 0.26903133;
  double neighborhood_weight = 0.37388647;
  double late_weight = 0.17000431;
  double critical_weight = 0.04395385;
  unsigned budget = 40;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
