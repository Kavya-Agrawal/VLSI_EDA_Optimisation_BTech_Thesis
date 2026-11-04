// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17773379;
  double density_weight = 0.38489453;
  double prefix_weight = 0.37697620;
  double neighborhood_weight = 0.28822011;
  double late_weight = 0.09366692;
  double critical_weight = 0.10943510;
  unsigned budget = 20;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
