// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08630897;
  double density_weight = 0.17020971;
  double prefix_weight = 0.22133400;
  double neighborhood_weight = 0.34811132;
  double late_weight = 0.15071072;
  double critical_weight = 0.06796262;
  unsigned budget = 28;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
