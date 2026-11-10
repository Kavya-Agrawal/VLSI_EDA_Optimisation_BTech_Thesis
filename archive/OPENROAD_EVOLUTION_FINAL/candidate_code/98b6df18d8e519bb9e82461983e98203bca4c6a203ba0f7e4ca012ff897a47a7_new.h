// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10820239;
  double density_weight = 0.30798033;
  double prefix_weight = 0.17676015;
  double neighborhood_weight = 0.12655659;
  double late_weight = 0.13689049;
  double critical_weight = 0.20812374;
  unsigned budget = 22;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
