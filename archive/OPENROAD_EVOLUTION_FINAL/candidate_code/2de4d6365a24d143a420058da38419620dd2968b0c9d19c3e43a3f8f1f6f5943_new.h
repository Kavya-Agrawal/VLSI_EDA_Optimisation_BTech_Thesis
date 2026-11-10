// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45063332;
  double density_weight = 0.39341997;
  double prefix_weight = 0.09492079;
  double neighborhood_weight = 0.32375871;
  double late_weight = 0.18032713;
  double critical_weight = 0.40972565;
  unsigned budget = 13;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
