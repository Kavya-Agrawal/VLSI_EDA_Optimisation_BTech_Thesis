// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92694001;
  double density_weight = 0.36916141;
  double prefix_weight = 0.36753097;
  double neighborhood_weight = 0.01215948;
  double late_weight = 0.20958555;
  double critical_weight = 0.10252812;
  unsigned budget = 21;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
