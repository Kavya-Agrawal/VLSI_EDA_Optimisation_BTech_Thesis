// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33768119;
  double density_weight = 0.08509214;
  double prefix_weight = 0.41616085;
  double neighborhood_weight = 0.18767793;
  double late_weight = 0.19163542;
  double critical_weight = 0.04418138;
  unsigned budget = 8;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
