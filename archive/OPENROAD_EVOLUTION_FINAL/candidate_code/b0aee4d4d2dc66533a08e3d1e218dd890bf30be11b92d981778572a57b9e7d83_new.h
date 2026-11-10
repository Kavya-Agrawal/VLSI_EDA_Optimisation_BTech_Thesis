// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06435870;
  double density_weight = 0.17402826;
  double prefix_weight = 0.44060338;
  double neighborhood_weight = 0.17287246;
  double late_weight = 0.18256229;
  double critical_weight = 0.08959628;
  unsigned budget = 7;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
