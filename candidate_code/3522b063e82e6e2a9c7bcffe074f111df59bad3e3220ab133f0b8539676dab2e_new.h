// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94263475;
  double density_weight = 0.23606752;
  double prefix_weight = 0.12590445;
  double neighborhood_weight = 0.17785301;
  double late_weight = 0.05958373;
  double critical_weight = 0.07513483;
  unsigned budget = 31;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
