// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41566634;
  double density_weight = 0.42816740;
  double prefix_weight = 0.44208327;
  double neighborhood_weight = 0.28901888;
  double late_weight = 0.08141885;
  double critical_weight = 0.13355265;
  unsigned budget = 26;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
