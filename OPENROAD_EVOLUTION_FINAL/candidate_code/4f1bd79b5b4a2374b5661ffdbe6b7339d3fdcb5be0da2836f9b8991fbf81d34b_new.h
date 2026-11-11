// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57472275;
  double density_weight = 0.28357295;
  double prefix_weight = 0.31021829;
  double neighborhood_weight = 0.34440337;
  double late_weight = 0.17653586;
  double critical_weight = 0.16538582;
  unsigned budget = 23;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
