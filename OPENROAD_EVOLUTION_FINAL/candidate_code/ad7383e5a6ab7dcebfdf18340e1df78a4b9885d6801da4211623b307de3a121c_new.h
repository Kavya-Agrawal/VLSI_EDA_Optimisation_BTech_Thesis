// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76189006;
  double density_weight = 0.46206108;
  double prefix_weight = 0.23896269;
  double neighborhood_weight = 0.21771431;
  double late_weight = 0.20389346;
  double critical_weight = 0.20064991;
  unsigned budget = 11;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
