// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28797049;
  double density_weight = 0.41032501;
  double prefix_weight = 0.03401765;
  double neighborhood_weight = 0.30359046;
  double late_weight = 0.20187815;
  double critical_weight = 0.01601605;
  unsigned budget = 30;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
