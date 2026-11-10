// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64709290;
  double density_weight = 0.19878140;
  double prefix_weight = 0.09632828;
  double neighborhood_weight = 0.24765344;
  double late_weight = 0.16328831;
  double critical_weight = 0.10495853;
  unsigned budget = 18;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
