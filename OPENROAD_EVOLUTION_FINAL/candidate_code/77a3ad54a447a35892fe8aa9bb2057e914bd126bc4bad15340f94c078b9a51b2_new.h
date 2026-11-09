// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37280644;
  double density_weight = 0.46812751;
  double prefix_weight = 0.02234873;
  double neighborhood_weight = 0.23433000;
  double late_weight = 0.12129637;
  double critical_weight = 0.15786356;
  unsigned budget = 14;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
