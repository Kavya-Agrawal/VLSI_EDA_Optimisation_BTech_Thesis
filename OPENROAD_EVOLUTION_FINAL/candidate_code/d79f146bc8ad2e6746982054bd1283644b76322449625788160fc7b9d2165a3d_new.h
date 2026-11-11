// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42938414;
  double density_weight = 0.43777717;
  double prefix_weight = 0.32417330;
  double neighborhood_weight = 0.12534787;
  double late_weight = 0.03441103;
  double critical_weight = 0.29196967;
  unsigned budget = 9;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
