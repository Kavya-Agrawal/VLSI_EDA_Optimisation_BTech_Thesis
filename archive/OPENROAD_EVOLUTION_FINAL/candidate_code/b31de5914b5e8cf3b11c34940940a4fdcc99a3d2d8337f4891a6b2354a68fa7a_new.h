// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71294811;
  double density_weight = 0.02981384;
  double prefix_weight = 0.29646361;
  double neighborhood_weight = 0.17429038;
  double late_weight = 0.22762529;
  double critical_weight = 0.22440209;
  unsigned budget = 34;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
