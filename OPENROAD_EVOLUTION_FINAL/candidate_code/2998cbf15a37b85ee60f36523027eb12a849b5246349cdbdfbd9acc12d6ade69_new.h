// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11434900;
  double density_weight = 0.28766318;
  double prefix_weight = 0.43407589;
  double neighborhood_weight = 0.15653640;
  double late_weight = 0.13293045;
  double critical_weight = 0.27052161;
  unsigned budget = 28;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
