// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29159527;
  double density_weight = 0.28559434;
  double prefix_weight = 0.11773957;
  double neighborhood_weight = 0.07828437;
  double late_weight = 0.00376940;
  double critical_weight = 0.18503316;
  unsigned budget = 8;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
