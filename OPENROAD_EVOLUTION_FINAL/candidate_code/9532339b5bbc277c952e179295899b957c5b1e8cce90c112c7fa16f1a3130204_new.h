// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14839630;
  double density_weight = 0.37757830;
  double prefix_weight = 0.21268608;
  double neighborhood_weight = 0.29185813;
  double late_weight = 0.00140427;
  double critical_weight = 0.06289469;
  unsigned budget = 10;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
