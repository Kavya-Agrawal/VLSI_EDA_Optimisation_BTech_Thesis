// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59159009;
  double density_weight = 0.23151211;
  double prefix_weight = 0.29345728;
  double neighborhood_weight = 0.05523853;
  double late_weight = 0.22013444;
  double critical_weight = 0.00757205;
  unsigned budget = 7;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
