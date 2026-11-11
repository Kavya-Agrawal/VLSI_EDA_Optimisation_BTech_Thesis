// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25710738;
  double density_weight = 0.13752579;
  double prefix_weight = 0.06159381;
  double neighborhood_weight = 0.16322070;
  double late_weight = 0.11809245;
  double critical_weight = 0.15714170;
  unsigned budget = 30;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
