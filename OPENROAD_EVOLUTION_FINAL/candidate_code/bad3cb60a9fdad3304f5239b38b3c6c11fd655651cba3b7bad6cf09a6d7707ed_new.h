// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42360223;
  double density_weight = 0.53756419;
  double prefix_weight = 0.02243493;
  double neighborhood_weight = 0.25225649;
  double late_weight = 0.28727716;
  double critical_weight = 0.17077993;
  unsigned budget = 26;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
