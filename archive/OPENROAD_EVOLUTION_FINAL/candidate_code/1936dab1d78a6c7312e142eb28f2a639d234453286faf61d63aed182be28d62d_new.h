// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97121036;
  double density_weight = 0.31646027;
  double prefix_weight = 0.36763988;
  double neighborhood_weight = 0.33962978;
  double late_weight = 0.17095147;
  double critical_weight = 0.33601116;
  unsigned budget = 26;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
