// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00336870;
  double density_weight = 0.52368607;
  double prefix_weight = 0.32949857;
  double neighborhood_weight = 0.29132469;
  double late_weight = 0.11823489;
  double critical_weight = 0.19947540;
  unsigned budget = 20;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
