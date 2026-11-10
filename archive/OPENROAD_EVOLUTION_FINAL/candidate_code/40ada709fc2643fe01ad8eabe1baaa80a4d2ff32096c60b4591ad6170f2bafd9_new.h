// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76300193;
  double density_weight = 0.39447872;
  double prefix_weight = 0.34242909;
  double neighborhood_weight = 0.26642015;
  double late_weight = 0.10604693;
  double critical_weight = 0.05003109;
  unsigned budget = 25;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
