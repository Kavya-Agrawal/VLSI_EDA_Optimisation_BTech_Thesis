// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96197599;
  double density_weight = 0.10565492;
  double prefix_weight = 0.38395011;
  double neighborhood_weight = 0.31019522;
  double late_weight = 0.01507201;
  double critical_weight = 0.20217507;
  unsigned budget = 32;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
