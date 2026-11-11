// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28684253;
  double density_weight = 0.17883370;
  double prefix_weight = 0.16917031;
  double neighborhood_weight = 0.36867292;
  double late_weight = 0.07781774;
  double critical_weight = 0.27504538;
  unsigned budget = 22;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
