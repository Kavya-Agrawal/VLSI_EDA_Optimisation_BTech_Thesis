// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89865904;
  double density_weight = 0.58422091;
  double prefix_weight = 0.12719471;
  double neighborhood_weight = 0.28242284;
  double late_weight = 0.09507067;
  double critical_weight = 0.44567021;
  unsigned budget = 32;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
