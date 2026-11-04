// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81152830;
  double density_weight = 0.29711790;
  double prefix_weight = 0.39438456;
  double neighborhood_weight = 0.17464146;
  double late_weight = 0.16292980;
  double critical_weight = 0.31345282;
  unsigned budget = 32;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
