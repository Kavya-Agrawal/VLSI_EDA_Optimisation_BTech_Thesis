// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48051480;
  double density_weight = 0.26877195;
  double prefix_weight = 0.04080879;
  double neighborhood_weight = 0.30034651;
  double late_weight = 0.03907669;
  double critical_weight = 0.43754443;
  unsigned budget = 4;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
