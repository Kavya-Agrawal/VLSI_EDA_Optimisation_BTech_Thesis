// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65706712;
  double density_weight = 0.10282016;
  double prefix_weight = 0.16697102;
  double neighborhood_weight = 0.16800722;
  double late_weight = 0.09447627;
  double critical_weight = 0.36455842;
  unsigned budget = 36;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
