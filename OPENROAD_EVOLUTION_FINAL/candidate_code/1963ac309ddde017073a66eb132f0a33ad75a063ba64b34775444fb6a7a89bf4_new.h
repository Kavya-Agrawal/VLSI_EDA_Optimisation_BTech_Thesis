// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21628501;
  double density_weight = 0.44209832;
  double prefix_weight = 0.33171387;
  double neighborhood_weight = 0.12005681;
  double late_weight = 0.29617561;
  double critical_weight = 0.35718682;
  unsigned budget = 37;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
