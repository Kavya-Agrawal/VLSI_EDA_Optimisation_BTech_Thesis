// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16784962;
  double density_weight = 0.01990078;
  double prefix_weight = 0.43786333;
  double neighborhood_weight = 0.30402187;
  double late_weight = 0.10204019;
  double critical_weight = 0.10281630;
  unsigned budget = 38;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
