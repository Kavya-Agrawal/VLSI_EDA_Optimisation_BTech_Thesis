// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33895882;
  double density_weight = 0.36752015;
  double prefix_weight = 0.48766904;
  double neighborhood_weight = 0.03149827;
  double late_weight = 0.08155576;
  double critical_weight = 0.19896187;
  unsigned budget = 39;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
