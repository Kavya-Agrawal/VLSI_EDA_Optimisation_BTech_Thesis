// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44444042;
  double density_weight = 0.13675883;
  double prefix_weight = 0.12819805;
  double neighborhood_weight = 0.03008862;
  double late_weight = 0.26986793;
  double critical_weight = 0.05328641;
  unsigned budget = 12;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
