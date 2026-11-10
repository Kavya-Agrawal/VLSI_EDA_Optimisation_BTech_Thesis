// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48951412;
  double density_weight = 0.47865170;
  double prefix_weight = 0.08794998;
  double neighborhood_weight = 0.36980448;
  double late_weight = 0.05401162;
  double critical_weight = 0.12495932;
  unsigned budget = 11;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
