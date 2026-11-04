// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79400798;
  double density_weight = 0.47657510;
  double prefix_weight = 0.38602952;
  double neighborhood_weight = 0.30858758;
  double late_weight = 0.23679604;
  double critical_weight = 0.37090580;
  unsigned budget = 27;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
