// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75632485;
  double density_weight = 0.30475573;
  double prefix_weight = 0.43267832;
  double neighborhood_weight = 0.04927925;
  double late_weight = 0.03266471;
  double critical_weight = 0.48136306;
  unsigned budget = 18;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
