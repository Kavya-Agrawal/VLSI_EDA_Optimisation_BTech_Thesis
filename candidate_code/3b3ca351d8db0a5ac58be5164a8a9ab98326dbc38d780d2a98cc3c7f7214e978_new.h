// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70534106;
  double density_weight = 0.51977949;
  double prefix_weight = 0.15985750;
  double neighborhood_weight = 0.05416743;
  double late_weight = 0.26614503;
  double critical_weight = 0.46556499;
  unsigned budget = 29;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
