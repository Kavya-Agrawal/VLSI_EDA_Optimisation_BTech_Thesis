// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63611506;
  double density_weight = 0.30641260;
  double prefix_weight = 0.31843033;
  double neighborhood_weight = 0.16867046;
  double late_weight = 0.23324139;
  double critical_weight = 0.01214185;
  unsigned budget = 11;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
