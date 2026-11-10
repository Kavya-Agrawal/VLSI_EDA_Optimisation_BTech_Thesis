// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21520407;
  double density_weight = 0.34234189;
  double prefix_weight = 0.14050322;
  double neighborhood_weight = 0.05645859;
  double late_weight = 0.17132134;
  double critical_weight = 0.23485803;
  unsigned budget = 14;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
