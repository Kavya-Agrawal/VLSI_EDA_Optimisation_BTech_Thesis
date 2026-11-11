// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30239890;
  double density_weight = 0.01545087;
  double prefix_weight = 0.44925943;
  double neighborhood_weight = 0.01997537;
  double late_weight = 0.04931830;
  double critical_weight = 0.19772881;
  unsigned budget = 14;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
