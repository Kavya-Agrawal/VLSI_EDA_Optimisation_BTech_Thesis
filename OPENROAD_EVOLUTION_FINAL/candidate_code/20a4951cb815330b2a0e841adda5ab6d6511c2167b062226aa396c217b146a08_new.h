// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35158505;
  double density_weight = 0.24462591;
  double prefix_weight = 0.03364107;
  double neighborhood_weight = 0.34367639;
  double late_weight = 0.22804030;
  double critical_weight = 0.30089342;
  unsigned budget = 7;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
