// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22996653;
  double density_weight = 0.59018929;
  double prefix_weight = 0.33217920;
  double neighborhood_weight = 0.29036928;
  double late_weight = 0.12272100;
  double critical_weight = 0.07206371;
  unsigned budget = 35;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
