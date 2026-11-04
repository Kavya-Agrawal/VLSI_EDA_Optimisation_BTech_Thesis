// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19842347;
  double density_weight = 0.38198332;
  double prefix_weight = 0.08280910;
  double neighborhood_weight = 0.29461308;
  double late_weight = 0.20082592;
  double critical_weight = 0.06696850;
  unsigned budget = 36;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
