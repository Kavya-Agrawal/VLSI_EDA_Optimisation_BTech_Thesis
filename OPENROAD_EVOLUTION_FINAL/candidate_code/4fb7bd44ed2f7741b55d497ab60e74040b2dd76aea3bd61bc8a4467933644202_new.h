// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16715388;
  double density_weight = 0.25158800;
  double prefix_weight = 0.06694335;
  double neighborhood_weight = 0.38708062;
  double late_weight = 0.10267714;
  double critical_weight = 0.04493778;
  unsigned budget = 6;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
