// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36266824;
  double density_weight = 0.30118541;
  double prefix_weight = 0.39049133;
  double neighborhood_weight = 0.21368821;
  double late_weight = 0.26403545;
  double critical_weight = 0.28440071;
  unsigned budget = 28;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
