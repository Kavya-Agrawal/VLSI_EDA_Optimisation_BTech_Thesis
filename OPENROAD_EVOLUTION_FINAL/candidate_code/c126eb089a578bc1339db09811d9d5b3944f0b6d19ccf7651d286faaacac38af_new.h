// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58832647;
  double density_weight = 0.45004328;
  double prefix_weight = 0.30938190;
  double neighborhood_weight = 0.15092443;
  double late_weight = 0.02215473;
  double critical_weight = 0.01466029;
  unsigned budget = 27;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
