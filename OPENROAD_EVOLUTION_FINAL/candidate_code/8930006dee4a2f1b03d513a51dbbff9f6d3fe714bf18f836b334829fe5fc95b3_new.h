// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02622361;
  double density_weight = 0.31957663;
  double prefix_weight = 0.36450468;
  double neighborhood_weight = 0.25669313;
  double late_weight = 0.05478788;
  double critical_weight = 0.03888715;
  unsigned budget = 6;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
