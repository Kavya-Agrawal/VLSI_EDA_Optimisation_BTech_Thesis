// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88800409;
  double density_weight = 0.35835184;
  double prefix_weight = 0.05102971;
  double neighborhood_weight = 0.29163500;
  double late_weight = 0.10279054;
  double critical_weight = 0.02821287;
  unsigned budget = 26;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
