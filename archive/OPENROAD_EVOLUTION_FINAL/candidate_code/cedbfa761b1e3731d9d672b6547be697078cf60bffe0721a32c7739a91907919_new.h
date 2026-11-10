// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57047817;
  double density_weight = 0.59110316;
  double prefix_weight = 0.02895599;
  double neighborhood_weight = 0.39869754;
  double late_weight = 0.06452032;
  double critical_weight = 0.11917636;
  unsigned budget = 24;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
