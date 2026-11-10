// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19768792;
  double density_weight = 0.37039799;
  double prefix_weight = 0.24083377;
  double neighborhood_weight = 0.16564236;
  double late_weight = 0.07571078;
  double critical_weight = 0.21821405;
  unsigned budget = 13;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
