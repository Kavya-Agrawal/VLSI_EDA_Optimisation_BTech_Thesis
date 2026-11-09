// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31242880;
  double density_weight = 0.37100915;
  double prefix_weight = 0.32909924;
  double neighborhood_weight = 0.39967800;
  double late_weight = 0.05168384;
  double critical_weight = 0.11224578;
  unsigned budget = 14;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
