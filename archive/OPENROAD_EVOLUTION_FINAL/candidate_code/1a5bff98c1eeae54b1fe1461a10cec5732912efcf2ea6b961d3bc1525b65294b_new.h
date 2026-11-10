// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22075689;
  double density_weight = 0.13479113;
  double prefix_weight = 0.11864953;
  double neighborhood_weight = 0.37079409;
  double late_weight = 0.22640206;
  double critical_weight = 0.11243739;
  unsigned budget = 12;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
