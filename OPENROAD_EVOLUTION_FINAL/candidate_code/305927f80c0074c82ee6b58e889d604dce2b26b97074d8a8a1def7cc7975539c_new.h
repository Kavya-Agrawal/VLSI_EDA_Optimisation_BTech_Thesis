// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43012189;
  double density_weight = 0.00281668;
  double prefix_weight = 0.34688422;
  double neighborhood_weight = 0.33181561;
  double late_weight = 0.06071837;
  double critical_weight = 0.24818058;
  unsigned budget = 29;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
