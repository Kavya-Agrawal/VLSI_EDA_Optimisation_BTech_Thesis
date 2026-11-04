// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17163497;
  double density_weight = 0.33539579;
  double prefix_weight = 0.07027242;
  double neighborhood_weight = 0.24297283;
  double late_weight = 0.29566926;
  double critical_weight = 0.38401085;
  unsigned budget = 8;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
