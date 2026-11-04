// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13972590;
  double density_weight = 0.19616417;
  double prefix_weight = 0.49729597;
  double neighborhood_weight = 0.16760142;
  double late_weight = 0.22172268;
  double critical_weight = 0.32359863;
  unsigned budget = 12;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
