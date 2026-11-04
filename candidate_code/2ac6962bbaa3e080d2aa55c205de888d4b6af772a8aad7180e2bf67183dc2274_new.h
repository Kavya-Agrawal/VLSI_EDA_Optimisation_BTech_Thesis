// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85140440;
  double density_weight = 0.53430509;
  double prefix_weight = 0.03407785;
  double neighborhood_weight = 0.04826419;
  double late_weight = 0.12510708;
  double critical_weight = 0.01607610;
  unsigned budget = 7;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
