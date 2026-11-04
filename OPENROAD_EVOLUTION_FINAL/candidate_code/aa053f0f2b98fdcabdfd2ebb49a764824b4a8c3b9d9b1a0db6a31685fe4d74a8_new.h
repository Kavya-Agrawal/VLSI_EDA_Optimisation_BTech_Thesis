// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92395682;
  double density_weight = 0.42537414;
  double prefix_weight = 0.12734765;
  double neighborhood_weight = 0.07660269;
  double late_weight = 0.02566523;
  double critical_weight = 0.20869563;
  unsigned budget = 6;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
