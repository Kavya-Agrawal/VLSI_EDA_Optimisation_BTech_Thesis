// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57597470;
  double density_weight = 0.27778483;
  double prefix_weight = 0.08985252;
  double neighborhood_weight = 0.38975687;
  double late_weight = 0.26035276;
  double critical_weight = 0.05912642;
  unsigned budget = 19;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
