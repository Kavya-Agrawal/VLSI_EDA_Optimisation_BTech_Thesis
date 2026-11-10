// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65561996;
  double density_weight = 0.15798777;
  double prefix_weight = 0.33551811;
  double neighborhood_weight = 0.20950527;
  double late_weight = 0.01039274;
  double critical_weight = 0.33057062;
  unsigned budget = 20;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
