// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02493476;
  double density_weight = 0.25400081;
  double prefix_weight = 0.29659372;
  double neighborhood_weight = 0.29326520;
  double late_weight = 0.21288948;
  double critical_weight = 0.33289593;
  unsigned budget = 24;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
