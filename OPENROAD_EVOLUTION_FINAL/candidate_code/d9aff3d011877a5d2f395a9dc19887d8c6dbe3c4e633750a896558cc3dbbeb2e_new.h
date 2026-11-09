// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83259941;
  double density_weight = 0.48404241;
  double prefix_weight = 0.00248348;
  double neighborhood_weight = 0.00566866;
  double late_weight = 0.24438302;
  double critical_weight = 0.20147357;
  unsigned budget = 39;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
