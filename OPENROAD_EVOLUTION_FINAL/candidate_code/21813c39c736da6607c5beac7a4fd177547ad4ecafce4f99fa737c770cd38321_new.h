// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09708251;
  double density_weight = 0.06403015;
  double prefix_weight = 0.19430913;
  double neighborhood_weight = 0.13102612;
  double late_weight = 0.08325584;
  double critical_weight = 0.31943971;
  unsigned budget = 13;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
