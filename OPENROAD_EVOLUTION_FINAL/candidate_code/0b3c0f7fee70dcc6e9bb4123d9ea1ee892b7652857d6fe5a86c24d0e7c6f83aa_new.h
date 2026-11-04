// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82282742;
  double density_weight = 0.19899457;
  double prefix_weight = 0.42559514;
  double neighborhood_weight = 0.14583248;
  double late_weight = 0.15142052;
  double critical_weight = 0.01808630;
  unsigned budget = 12;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
