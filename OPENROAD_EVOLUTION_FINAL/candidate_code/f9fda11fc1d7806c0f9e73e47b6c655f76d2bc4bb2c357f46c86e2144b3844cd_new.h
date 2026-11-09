// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87113767;
  double density_weight = 0.05323586;
  double prefix_weight = 0.21473844;
  double neighborhood_weight = 0.08945289;
  double late_weight = 0.09311709;
  double critical_weight = 0.05340408;
  unsigned budget = 9;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
