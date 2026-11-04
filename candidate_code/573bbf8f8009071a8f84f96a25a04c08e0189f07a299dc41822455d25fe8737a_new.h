// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20795533;
  double density_weight = 0.12623580;
  double prefix_weight = 0.35220396;
  double neighborhood_weight = 0.07783459;
  double late_weight = 0.27573091;
  double critical_weight = 0.13337266;
  unsigned budget = 23;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
