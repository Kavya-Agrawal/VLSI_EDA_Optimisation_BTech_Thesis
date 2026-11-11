// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45551176;
  double density_weight = 0.34906931;
  double prefix_weight = 0.32371135;
  double neighborhood_weight = 0.07150365;
  double late_weight = 0.00700076;
  double critical_weight = 0.00156123;
  unsigned budget = 20;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
