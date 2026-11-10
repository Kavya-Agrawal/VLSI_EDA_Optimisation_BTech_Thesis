// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40612748;
  double density_weight = 0.42982365;
  double prefix_weight = 0.25486493;
  double neighborhood_weight = 0.20948180;
  double late_weight = 0.28316795;
  double critical_weight = 0.27560365;
  unsigned budget = 32;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
