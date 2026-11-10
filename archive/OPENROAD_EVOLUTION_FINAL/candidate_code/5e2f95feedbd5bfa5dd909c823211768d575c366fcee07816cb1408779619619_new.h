// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45540461;
  double density_weight = 0.27967630;
  double prefix_weight = 0.08395283;
  double neighborhood_weight = 0.05519706;
  double late_weight = 0.11702389;
  double critical_weight = 0.07587125;
  unsigned budget = 20;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
