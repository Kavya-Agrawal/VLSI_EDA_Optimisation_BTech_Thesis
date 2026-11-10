// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41116860;
  double density_weight = 0.35892309;
  double prefix_weight = 0.48165706;
  double neighborhood_weight = 0.34046211;
  double late_weight = 0.23353034;
  double critical_weight = 0.31786732;
  unsigned budget = 4;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
