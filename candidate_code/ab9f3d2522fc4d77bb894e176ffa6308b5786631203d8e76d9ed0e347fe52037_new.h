// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79971846;
  double density_weight = 0.15770835;
  double prefix_weight = 0.41967459;
  double neighborhood_weight = 0.23778741;
  double late_weight = 0.20251484;
  double critical_weight = 0.30945377;
  unsigned budget = 32;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
