// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34548734;
  double density_weight = 0.16459345;
  double prefix_weight = 0.07835231;
  double neighborhood_weight = 0.14723998;
  double late_weight = 0.18565067;
  double critical_weight = 0.04316034;
  unsigned budget = 7;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
