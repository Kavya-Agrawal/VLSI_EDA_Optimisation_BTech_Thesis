// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10689795;
  double density_weight = 0.37013752;
  double prefix_weight = 0.26256029;
  double neighborhood_weight = 0.01156380;
  double late_weight = 0.09161613;
  double critical_weight = 0.06509336;
  unsigned budget = 39;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
