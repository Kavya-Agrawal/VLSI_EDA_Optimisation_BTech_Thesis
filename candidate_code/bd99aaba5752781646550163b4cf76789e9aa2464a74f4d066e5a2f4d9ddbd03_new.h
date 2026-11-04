// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85049288;
  double density_weight = 0.51072907;
  double prefix_weight = 0.24489548;
  double neighborhood_weight = 0.02187744;
  double late_weight = 0.04831921;
  double critical_weight = 0.45088679;
  unsigned budget = 14;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
