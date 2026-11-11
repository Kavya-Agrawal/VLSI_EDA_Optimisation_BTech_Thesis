// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92834865;
  double density_weight = 0.33498095;
  double prefix_weight = 0.45011057;
  double neighborhood_weight = 0.10036046;
  double late_weight = 0.21775579;
  double critical_weight = 0.16593341;
  unsigned budget = 29;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
