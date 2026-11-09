// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49575814;
  double density_weight = 0.14630587;
  double prefix_weight = 0.03333746;
  double neighborhood_weight = 0.08805531;
  double late_weight = 0.25979170;
  double critical_weight = 0.18991254;
  unsigned budget = 36;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
