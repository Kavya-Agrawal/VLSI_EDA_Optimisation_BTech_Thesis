// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63784355;
  double density_weight = 0.33058313;
  double prefix_weight = 0.24442953;
  double neighborhood_weight = 0.39536939;
  double late_weight = 0.22660209;
  double critical_weight = 0.02105698;
  unsigned budget = 30;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
