// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30591755;
  double density_weight = 0.52660498;
  double prefix_weight = 0.26725043;
  double neighborhood_weight = 0.29989403;
  double late_weight = 0.07140347;
  double critical_weight = 0.39591869;
  unsigned budget = 9;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
