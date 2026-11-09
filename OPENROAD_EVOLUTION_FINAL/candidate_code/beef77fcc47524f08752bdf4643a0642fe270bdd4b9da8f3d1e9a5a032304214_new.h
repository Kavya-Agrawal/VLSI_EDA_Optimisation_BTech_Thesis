// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81671260;
  double density_weight = 0.11401371;
  double prefix_weight = 0.31159389;
  double neighborhood_weight = 0.01279639;
  double late_weight = 0.26770698;
  double critical_weight = 0.00455624;
  unsigned budget = 36;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
