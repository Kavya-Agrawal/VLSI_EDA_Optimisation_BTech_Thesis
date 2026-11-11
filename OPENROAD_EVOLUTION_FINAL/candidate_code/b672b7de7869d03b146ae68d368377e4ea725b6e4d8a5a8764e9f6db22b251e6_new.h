// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71314396;
  double density_weight = 0.32316168;
  double prefix_weight = 0.25813155;
  double neighborhood_weight = 0.19222226;
  double late_weight = 0.18011340;
  double critical_weight = 0.31899011;
  unsigned budget = 4;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
