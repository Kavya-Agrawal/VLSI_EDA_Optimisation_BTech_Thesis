// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64589705;
  double density_weight = 0.20840109;
  double prefix_weight = 0.25457267;
  double neighborhood_weight = 0.28272738;
  double late_weight = 0.20580995;
  double critical_weight = 0.47666161;
  unsigned budget = 30;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
