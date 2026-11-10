// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54739064;
  double density_weight = 0.39501241;
  double prefix_weight = 0.44821531;
  double neighborhood_weight = 0.01048550;
  double late_weight = 0.04088327;
  double critical_weight = 0.02329620;
  unsigned budget = 20;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
