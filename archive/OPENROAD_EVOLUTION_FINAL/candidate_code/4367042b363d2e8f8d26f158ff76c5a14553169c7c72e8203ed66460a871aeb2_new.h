// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47395268;
  double density_weight = 0.13135623;
  double prefix_weight = 0.39604895;
  double neighborhood_weight = 0.37666394;
  double late_weight = 0.06346745;
  double critical_weight = 0.35607931;
  unsigned budget = 27;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
