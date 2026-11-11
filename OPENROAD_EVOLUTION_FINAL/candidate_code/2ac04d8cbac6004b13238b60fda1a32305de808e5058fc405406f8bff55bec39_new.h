// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05198597;
  double density_weight = 0.18354095;
  double prefix_weight = 0.03884706;
  double neighborhood_weight = 0.27254934;
  double late_weight = 0.16648385;
  double critical_weight = 0.04749722;
  unsigned budget = 26;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
