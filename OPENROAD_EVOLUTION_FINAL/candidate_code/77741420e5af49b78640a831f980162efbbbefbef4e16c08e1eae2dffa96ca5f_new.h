// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02089375;
  double density_weight = 0.22615030;
  double prefix_weight = 0.17223769;
  double neighborhood_weight = 0.26353888;
  double late_weight = 0.01819431;
  double critical_weight = 0.05814844;
  unsigned budget = 40;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
