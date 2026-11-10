// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48350833;
  double density_weight = 0.32155271;
  double prefix_weight = 0.21019781;
  double neighborhood_weight = 0.16121150;
  double late_weight = 0.01224417;
  double critical_weight = 0.17210006;
  unsigned budget = 20;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
