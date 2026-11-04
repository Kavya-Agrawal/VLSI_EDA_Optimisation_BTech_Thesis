// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29828687;
  double density_weight = 0.05929285;
  double prefix_weight = 0.00751001;
  double neighborhood_weight = 0.12758051;
  double late_weight = 0.16227059;
  double critical_weight = 0.45505187;
  unsigned budget = 11;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
