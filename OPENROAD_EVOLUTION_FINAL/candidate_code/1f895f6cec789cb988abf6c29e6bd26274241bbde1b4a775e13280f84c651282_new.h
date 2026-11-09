// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08000691;
  double density_weight = 0.17614657;
  double prefix_weight = 0.32755673;
  double neighborhood_weight = 0.37945050;
  double late_weight = 0.24001183;
  double critical_weight = 0.21781736;
  unsigned budget = 39;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
