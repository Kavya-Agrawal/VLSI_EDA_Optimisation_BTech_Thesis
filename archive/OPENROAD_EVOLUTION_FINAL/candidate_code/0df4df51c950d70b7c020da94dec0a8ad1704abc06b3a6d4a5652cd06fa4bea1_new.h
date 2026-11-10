// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89334926;
  double density_weight = 0.45460053;
  double prefix_weight = 0.25146050;
  double neighborhood_weight = 0.26618491;
  double late_weight = 0.12573120;
  double critical_weight = 0.42313292;
  unsigned budget = 35;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
