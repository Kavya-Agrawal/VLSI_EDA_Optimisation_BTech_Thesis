// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68388368;
  double density_weight = 0.17409193;
  double prefix_weight = 0.46168474;
  double neighborhood_weight = 0.19914128;
  double late_weight = 0.01007525;
  double critical_weight = 0.44478031;
  unsigned budget = 21;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
