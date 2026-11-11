// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47315868;
  double density_weight = 0.48738144;
  double prefix_weight = 0.46179368;
  double neighborhood_weight = 0.07519556;
  double late_weight = 0.11240684;
  double critical_weight = 0.16321235;
  unsigned budget = 20;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
