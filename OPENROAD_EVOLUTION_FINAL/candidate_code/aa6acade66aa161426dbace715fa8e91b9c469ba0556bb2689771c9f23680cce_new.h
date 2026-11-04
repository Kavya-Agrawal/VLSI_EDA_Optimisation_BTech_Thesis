// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55143545;
  double density_weight = 0.41371917;
  double prefix_weight = 0.36129044;
  double neighborhood_weight = 0.25275534;
  double late_weight = 0.25116809;
  double critical_weight = 0.17190237;
  unsigned budget = 33;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
