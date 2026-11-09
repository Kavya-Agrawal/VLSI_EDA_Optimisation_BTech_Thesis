// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80369371;
  double density_weight = 0.15529443;
  double prefix_weight = 0.19570420;
  double neighborhood_weight = 0.20712323;
  double late_weight = 0.07287423;
  double critical_weight = 0.17677070;
  unsigned budget = 23;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
