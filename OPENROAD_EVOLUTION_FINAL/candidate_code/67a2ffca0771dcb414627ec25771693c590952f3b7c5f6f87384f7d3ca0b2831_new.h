// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74253620;
  double density_weight = 0.21824278;
  double prefix_weight = 0.19045044;
  double neighborhood_weight = 0.22383496;
  double late_weight = 0.28093428;
  double critical_weight = 0.46815847;
  unsigned budget = 27;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
