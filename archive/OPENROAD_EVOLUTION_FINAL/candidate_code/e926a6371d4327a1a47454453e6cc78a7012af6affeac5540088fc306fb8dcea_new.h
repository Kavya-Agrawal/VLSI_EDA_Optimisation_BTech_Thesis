// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65064505;
  double density_weight = 0.27071762;
  double prefix_weight = 0.38043454;
  double neighborhood_weight = 0.04193405;
  double late_weight = 0.21860318;
  double critical_weight = 0.45898590;
  unsigned budget = 11;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
