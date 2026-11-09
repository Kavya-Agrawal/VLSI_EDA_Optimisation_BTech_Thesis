// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47169072;
  double density_weight = 0.29613460;
  double prefix_weight = 0.06303259;
  double neighborhood_weight = 0.33948609;
  double late_weight = 0.20007830;
  double critical_weight = 0.27682915;
  unsigned budget = 18;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
