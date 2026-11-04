// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10925987;
  double density_weight = 0.42267941;
  double prefix_weight = 0.00048164;
  double neighborhood_weight = 0.17677596;
  double late_weight = 0.16567683;
  double critical_weight = 0.40464471;
  unsigned budget = 22;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
