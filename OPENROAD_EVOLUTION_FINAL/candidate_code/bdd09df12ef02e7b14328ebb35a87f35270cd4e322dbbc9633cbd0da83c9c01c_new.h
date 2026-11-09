// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92559217;
  double density_weight = 0.36252093;
  double prefix_weight = 0.04845164;
  double neighborhood_weight = 0.36696559;
  double late_weight = 0.15710417;
  double critical_weight = 0.37115614;
  unsigned budget = 6;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
