// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28079298;
  double density_weight = 0.19229585;
  double prefix_weight = 0.29606261;
  double neighborhood_weight = 0.35386585;
  double late_weight = 0.01807061;
  double critical_weight = 0.18561520;
  unsigned budget = 16;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
