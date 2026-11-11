// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48489011;
  double density_weight = 0.04528808;
  double prefix_weight = 0.17457122;
  double neighborhood_weight = 0.37326626;
  double late_weight = 0.09769347;
  double critical_weight = 0.36769556;
  unsigned budget = 20;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
