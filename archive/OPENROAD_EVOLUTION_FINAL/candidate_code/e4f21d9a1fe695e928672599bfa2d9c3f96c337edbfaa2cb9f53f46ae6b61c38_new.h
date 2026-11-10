// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65492887;
  double density_weight = 0.48480412;
  double prefix_weight = 0.36891659;
  double neighborhood_weight = 0.03624842;
  double late_weight = 0.27486911;
  double critical_weight = 0.38679117;
  unsigned budget = 33;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
