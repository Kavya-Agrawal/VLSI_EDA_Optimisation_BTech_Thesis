// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98118112;
  double density_weight = 0.27043021;
  double prefix_weight = 0.41581075;
  double neighborhood_weight = 0.02289683;
  double late_weight = 0.21973811;
  double critical_weight = 0.13210170;
  unsigned budget = 10;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
