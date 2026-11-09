// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68562053;
  double density_weight = 0.42895812;
  double prefix_weight = 0.31655987;
  double neighborhood_weight = 0.16776012;
  double late_weight = 0.07337884;
  double critical_weight = 0.21874952;
  unsigned budget = 23;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
