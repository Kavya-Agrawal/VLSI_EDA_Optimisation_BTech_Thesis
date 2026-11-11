// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82113364;
  double density_weight = 0.41586848;
  double prefix_weight = 0.26123276;
  double neighborhood_weight = 0.31110450;
  double late_weight = 0.08680540;
  double critical_weight = 0.16328938;
  unsigned budget = 14;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
