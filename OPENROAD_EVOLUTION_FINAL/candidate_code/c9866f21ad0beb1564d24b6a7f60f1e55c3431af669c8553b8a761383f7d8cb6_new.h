// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94092179;
  double density_weight = 0.55300993;
  double prefix_weight = 0.20567926;
  double neighborhood_weight = 0.11564984;
  double late_weight = 0.06016769;
  double critical_weight = 0.23333807;
  unsigned budget = 28;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
