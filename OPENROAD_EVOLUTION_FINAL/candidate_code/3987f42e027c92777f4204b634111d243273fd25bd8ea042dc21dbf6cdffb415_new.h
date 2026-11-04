// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09767269;
  double density_weight = 0.27945015;
  double prefix_weight = 0.43550156;
  double neighborhood_weight = 0.06440257;
  double late_weight = 0.18758405;
  double critical_weight = 0.09150565;
  unsigned budget = 19;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
