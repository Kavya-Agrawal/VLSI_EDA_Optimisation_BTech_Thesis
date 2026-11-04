// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18204810;
  double density_weight = 0.15411615;
  double prefix_weight = 0.07403953;
  double neighborhood_weight = 0.14377585;
  double late_weight = 0.08117917;
  double critical_weight = 0.34336641;
  unsigned budget = 7;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
