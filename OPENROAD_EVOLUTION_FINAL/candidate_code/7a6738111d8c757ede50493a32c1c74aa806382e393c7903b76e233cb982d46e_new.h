// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66056369;
  double density_weight = 0.05145679;
  double prefix_weight = 0.25731182;
  double neighborhood_weight = 0.38888367;
  double late_weight = 0.15177856;
  double critical_weight = 0.08930799;
  unsigned budget = 24;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
