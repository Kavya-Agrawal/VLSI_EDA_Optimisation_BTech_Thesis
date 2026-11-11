// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85375444;
  double density_weight = 0.36987171;
  double prefix_weight = 0.45869067;
  double neighborhood_weight = 0.28243475;
  double late_weight = 0.24781281;
  double critical_weight = 0.18525176;
  unsigned budget = 28;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
