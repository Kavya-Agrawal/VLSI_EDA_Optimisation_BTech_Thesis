// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49513799;
  double density_weight = 0.09421789;
  double prefix_weight = 0.07550129;
  double neighborhood_weight = 0.13274361;
  double late_weight = 0.04525980;
  double critical_weight = 0.17419634;
  unsigned budget = 35;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
