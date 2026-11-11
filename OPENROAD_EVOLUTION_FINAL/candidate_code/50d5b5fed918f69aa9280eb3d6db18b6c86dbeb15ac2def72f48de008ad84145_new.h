// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65102944;
  double density_weight = 0.35880577;
  double prefix_weight = 0.10483449;
  double neighborhood_weight = 0.33944173;
  double late_weight = 0.16064751;
  double critical_weight = 0.40835678;
  unsigned budget = 7;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
