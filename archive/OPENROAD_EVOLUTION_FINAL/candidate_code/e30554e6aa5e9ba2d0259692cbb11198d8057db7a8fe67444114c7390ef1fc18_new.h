// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31664132;
  double density_weight = 0.28610221;
  double prefix_weight = 0.43760820;
  double neighborhood_weight = 0.31634424;
  double late_weight = 0.10911654;
  double critical_weight = 0.08258285;
  unsigned budget = 22;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
