// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78329963;
  double density_weight = 0.48890470;
  double prefix_weight = 0.09081925;
  double neighborhood_weight = 0.35575557;
  double late_weight = 0.04734124;
  double critical_weight = 0.07131832;
  unsigned budget = 8;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
