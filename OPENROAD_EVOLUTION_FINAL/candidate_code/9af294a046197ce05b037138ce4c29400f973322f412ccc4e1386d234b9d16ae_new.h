// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98802101;
  double density_weight = 0.53836881;
  double prefix_weight = 0.19770101;
  double neighborhood_weight = 0.19546628;
  double late_weight = 0.21806051;
  double critical_weight = 0.02621612;
  unsigned budget = 15;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
