// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31848298;
  double density_weight = 0.16450755;
  double prefix_weight = 0.34505454;
  double neighborhood_weight = 0.15301679;
  double late_weight = 0.25966277;
  double critical_weight = 0.17130161;
  unsigned budget = 26;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
