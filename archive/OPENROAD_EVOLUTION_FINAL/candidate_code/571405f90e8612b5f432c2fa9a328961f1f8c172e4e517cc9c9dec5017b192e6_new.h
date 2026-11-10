// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26996297;
  double density_weight = 0.51712493;
  double prefix_weight = 0.16567962;
  double neighborhood_weight = 0.01578870;
  double late_weight = 0.02672871;
  double critical_weight = 0.17329695;
  unsigned budget = 12;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
