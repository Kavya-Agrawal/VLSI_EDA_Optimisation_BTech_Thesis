// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38253585;
  double density_weight = 0.31700583;
  double prefix_weight = 0.16594609;
  double neighborhood_weight = 0.12804535;
  double late_weight = 0.16622085;
  double critical_weight = 0.36462006;
  unsigned budget = 14;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
