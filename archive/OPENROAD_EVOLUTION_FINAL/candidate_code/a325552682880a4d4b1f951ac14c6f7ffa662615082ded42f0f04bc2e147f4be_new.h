// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23300851;
  double density_weight = 0.41670538;
  double prefix_weight = 0.14055272;
  double neighborhood_weight = 0.34918567;
  double late_weight = 0.02533264;
  double critical_weight = 0.33282392;
  unsigned budget = 19;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
