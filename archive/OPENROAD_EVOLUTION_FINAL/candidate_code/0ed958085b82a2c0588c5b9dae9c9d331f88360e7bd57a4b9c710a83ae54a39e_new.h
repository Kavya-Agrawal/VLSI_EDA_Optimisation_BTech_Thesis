// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78769008;
  double density_weight = 0.31762794;
  double prefix_weight = 0.01434490;
  double neighborhood_weight = 0.31388823;
  double late_weight = 0.00462467;
  double critical_weight = 0.44265410;
  unsigned budget = 35;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
