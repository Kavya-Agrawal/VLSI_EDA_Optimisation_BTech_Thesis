// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40478191;
  double density_weight = 0.28449898;
  double prefix_weight = 0.26680975;
  double neighborhood_weight = 0.05508201;
  double late_weight = 0.16434503;
  double critical_weight = 0.28738974;
  unsigned budget = 9;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
