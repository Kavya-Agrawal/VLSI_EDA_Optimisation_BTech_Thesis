// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20501547;
  double density_weight = 0.10914934;
  double prefix_weight = 0.01954787;
  double neighborhood_weight = 0.11384225;
  double late_weight = 0.20133419;
  double critical_weight = 0.12190728;
  unsigned budget = 17;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
