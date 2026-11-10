// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06168176;
  double density_weight = 0.59177452;
  double prefix_weight = 0.16403783;
  double neighborhood_weight = 0.09867625;
  double late_weight = 0.20537880;
  double critical_weight = 0.05422282;
  unsigned budget = 17;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
