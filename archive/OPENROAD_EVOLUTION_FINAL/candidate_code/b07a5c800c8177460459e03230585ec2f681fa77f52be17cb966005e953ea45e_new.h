// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62055069;
  double density_weight = 0.50325280;
  double prefix_weight = 0.05178224;
  double neighborhood_weight = 0.24432194;
  double late_weight = 0.02804237;
  double critical_weight = 0.07542604;
  unsigned budget = 32;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
