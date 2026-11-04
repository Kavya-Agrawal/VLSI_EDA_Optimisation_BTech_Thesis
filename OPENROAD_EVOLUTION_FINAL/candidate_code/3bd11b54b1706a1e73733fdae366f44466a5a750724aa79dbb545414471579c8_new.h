// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44171294;
  double density_weight = 0.06383661;
  double prefix_weight = 0.23449103;
  double neighborhood_weight = 0.18077393;
  double late_weight = 0.20249939;
  double critical_weight = 0.23386593;
  unsigned budget = 30;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
