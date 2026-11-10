// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50747150;
  double density_weight = 0.19030499;
  double prefix_weight = 0.11359031;
  double neighborhood_weight = 0.12143377;
  double late_weight = 0.24308216;
  double critical_weight = 0.14233562;
  unsigned budget = 5;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
