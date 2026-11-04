// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19908264;
  double density_weight = 0.20146840;
  double prefix_weight = 0.30030163;
  double neighborhood_weight = 0.06849123;
  double late_weight = 0.14253976;
  double critical_weight = 0.11862053;
  unsigned budget = 14;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
