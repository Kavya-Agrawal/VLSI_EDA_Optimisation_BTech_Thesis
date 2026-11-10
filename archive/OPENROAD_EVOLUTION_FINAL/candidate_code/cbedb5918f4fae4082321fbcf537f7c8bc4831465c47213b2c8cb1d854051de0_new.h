// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90439476;
  double density_weight = 0.29058344;
  double prefix_weight = 0.24068370;
  double neighborhood_weight = 0.25363413;
  double late_weight = 0.01823726;
  double critical_weight = 0.24576110;
  unsigned budget = 36;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
