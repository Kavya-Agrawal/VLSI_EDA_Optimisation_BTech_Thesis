// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01796517;
  double density_weight = 0.06328650;
  double prefix_weight = 0.19067055;
  double neighborhood_weight = 0.20512969;
  double late_weight = 0.06751953;
  double critical_weight = 0.27789790;
  unsigned budget = 14;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
