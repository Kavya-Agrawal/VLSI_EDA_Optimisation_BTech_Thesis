// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70510085;
  double density_weight = 0.10021049;
  double prefix_weight = 0.49172703;
  double neighborhood_weight = 0.28059317;
  double late_weight = 0.19806758;
  double critical_weight = 0.03082378;
  unsigned budget = 12;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
