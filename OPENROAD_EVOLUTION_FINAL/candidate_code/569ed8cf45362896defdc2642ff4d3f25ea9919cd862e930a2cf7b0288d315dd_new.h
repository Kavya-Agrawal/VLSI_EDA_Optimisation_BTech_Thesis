// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61358579;
  double density_weight = 0.52930524;
  double prefix_weight = 0.02665579;
  double neighborhood_weight = 0.38200915;
  double late_weight = 0.25694262;
  double critical_weight = 0.42646279;
  unsigned budget = 23;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
