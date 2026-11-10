// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47571610;
  double density_weight = 0.08638603;
  double prefix_weight = 0.04632907;
  double neighborhood_weight = 0.07578621;
  double late_weight = 0.24554199;
  double critical_weight = 0.27169797;
  unsigned budget = 33;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
