// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18987434;
  double density_weight = 0.08719598;
  double prefix_weight = 0.23954874;
  double neighborhood_weight = 0.03791027;
  double late_weight = 0.25003223;
  double critical_weight = 0.02432973;
  unsigned budget = 8;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
