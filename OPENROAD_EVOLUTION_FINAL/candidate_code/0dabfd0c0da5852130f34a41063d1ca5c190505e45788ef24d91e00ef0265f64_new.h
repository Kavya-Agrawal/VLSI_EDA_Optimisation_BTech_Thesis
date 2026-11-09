// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22259110;
  double density_weight = 0.50358398;
  double prefix_weight = 0.13330541;
  double neighborhood_weight = 0.23864031;
  double late_weight = 0.29725808;
  double critical_weight = 0.26916395;
  unsigned budget = 30;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
