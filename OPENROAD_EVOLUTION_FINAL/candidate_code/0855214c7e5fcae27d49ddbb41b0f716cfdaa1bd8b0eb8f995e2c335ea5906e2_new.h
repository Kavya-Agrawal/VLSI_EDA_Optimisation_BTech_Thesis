// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30230596;
  double density_weight = 0.32814933;
  double prefix_weight = 0.47344136;
  double neighborhood_weight = 0.15471904;
  double late_weight = 0.09006121;
  double critical_weight = 0.18533526;
  unsigned budget = 40;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
