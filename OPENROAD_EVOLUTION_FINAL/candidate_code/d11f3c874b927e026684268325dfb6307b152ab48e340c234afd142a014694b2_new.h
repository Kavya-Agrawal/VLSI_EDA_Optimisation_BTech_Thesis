// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73348747;
  double density_weight = 0.11221176;
  double prefix_weight = 0.18759235;
  double neighborhood_weight = 0.28003034;
  double late_weight = 0.03634434;
  double critical_weight = 0.34223015;
  unsigned budget = 16;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
