// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92953570;
  double density_weight = 0.01372994;
  double prefix_weight = 0.12460984;
  double neighborhood_weight = 0.05669472;
  double late_weight = 0.09109314;
  double critical_weight = 0.38551352;
  unsigned budget = 12;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
