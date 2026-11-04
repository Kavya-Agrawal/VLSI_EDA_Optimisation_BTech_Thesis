// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81735243;
  double density_weight = 0.58860469;
  double prefix_weight = 0.31703467;
  double neighborhood_weight = 0.24407366;
  double late_weight = 0.08749697;
  double critical_weight = 0.25959125;
  unsigned budget = 40;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
