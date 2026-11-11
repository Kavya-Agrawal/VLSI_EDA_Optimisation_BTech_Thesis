// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64118908;
  double density_weight = 0.33173238;
  double prefix_weight = 0.02341582;
  double neighborhood_weight = 0.08994874;
  double late_weight = 0.28758389;
  double critical_weight = 0.27677400;
  unsigned budget = 10;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
