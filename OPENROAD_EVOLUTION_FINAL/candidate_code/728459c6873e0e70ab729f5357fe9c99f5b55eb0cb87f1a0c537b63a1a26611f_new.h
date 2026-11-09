// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89279126;
  double density_weight = 0.22003820;
  double prefix_weight = 0.32164575;
  double neighborhood_weight = 0.02952050;
  double late_weight = 0.10883013;
  double critical_weight = 0.32071312;
  unsigned budget = 34;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
