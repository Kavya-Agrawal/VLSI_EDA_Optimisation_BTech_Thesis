// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20471714;
  double density_weight = 0.42511179;
  double prefix_weight = 0.31540759;
  double neighborhood_weight = 0.18205505;
  double late_weight = 0.19264560;
  double critical_weight = 0.34874463;
  unsigned budget = 29;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
