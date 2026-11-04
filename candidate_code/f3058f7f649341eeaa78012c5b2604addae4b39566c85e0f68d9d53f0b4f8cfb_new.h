// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04099261;
  double density_weight = 0.35458516;
  double prefix_weight = 0.16987980;
  double neighborhood_weight = 0.18583534;
  double late_weight = 0.00052346;
  double critical_weight = 0.31340236;
  unsigned budget = 26;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
