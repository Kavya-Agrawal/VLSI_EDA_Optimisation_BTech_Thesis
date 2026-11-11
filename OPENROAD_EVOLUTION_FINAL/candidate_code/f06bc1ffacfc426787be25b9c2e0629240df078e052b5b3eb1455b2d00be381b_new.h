// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78194420;
  double density_weight = 0.17848169;
  double prefix_weight = 0.28097171;
  double neighborhood_weight = 0.09148536;
  double late_weight = 0.18809632;
  double critical_weight = 0.14041505;
  unsigned budget = 22;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
