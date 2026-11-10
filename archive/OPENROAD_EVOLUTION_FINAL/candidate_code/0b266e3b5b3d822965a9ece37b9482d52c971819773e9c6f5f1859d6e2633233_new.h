// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59530154;
  double density_weight = 0.28727734;
  double prefix_weight = 0.36897743;
  double neighborhood_weight = 0.28236760;
  double late_weight = 0.20556312;
  double critical_weight = 0.20899246;
  unsigned budget = 7;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
