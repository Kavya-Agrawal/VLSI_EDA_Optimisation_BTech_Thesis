// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74679579;
  double density_weight = 0.35025857;
  double prefix_weight = 0.10674945;
  double neighborhood_weight = 0.20461486;
  double late_weight = 0.28247493;
  double critical_weight = 0.45826451;
  unsigned budget = 31;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
