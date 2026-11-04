// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83133287;
  double density_weight = 0.33895337;
  double prefix_weight = 0.06473043;
  double neighborhood_weight = 0.29638166;
  double late_weight = 0.20347975;
  double critical_weight = 0.24214057;
  unsigned budget = 37;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
