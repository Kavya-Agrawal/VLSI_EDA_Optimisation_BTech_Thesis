// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96506426;
  double density_weight = 0.23213726;
  double prefix_weight = 0.12790840;
  double neighborhood_weight = 0.32256733;
  double late_weight = 0.21717690;
  double critical_weight = 0.03060796;
  unsigned budget = 27;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
