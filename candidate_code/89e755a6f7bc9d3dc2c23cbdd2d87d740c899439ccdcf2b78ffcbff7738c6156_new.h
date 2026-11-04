// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41048458;
  double density_weight = 0.46524162;
  double prefix_weight = 0.05027952;
  double neighborhood_weight = 0.01502986;
  double late_weight = 0.00339896;
  double critical_weight = 0.28758683;
  unsigned budget = 19;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
