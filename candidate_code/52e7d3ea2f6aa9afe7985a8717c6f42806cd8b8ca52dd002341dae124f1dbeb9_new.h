// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03931893;
  double density_weight = 0.53174358;
  double prefix_weight = 0.07321418;
  double neighborhood_weight = 0.09296967;
  double late_weight = 0.15097483;
  double critical_weight = 0.40196883;
  unsigned budget = 11;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
