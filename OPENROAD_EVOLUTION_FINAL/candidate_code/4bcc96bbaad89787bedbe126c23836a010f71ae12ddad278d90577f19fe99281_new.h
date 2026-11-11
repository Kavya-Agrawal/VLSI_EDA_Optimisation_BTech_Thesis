// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35189272;
  double density_weight = 0.29360430;
  double prefix_weight = 0.03752960;
  double neighborhood_weight = 0.17661861;
  double late_weight = 0.18136537;
  double critical_weight = 0.19162284;
  unsigned budget = 33;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
