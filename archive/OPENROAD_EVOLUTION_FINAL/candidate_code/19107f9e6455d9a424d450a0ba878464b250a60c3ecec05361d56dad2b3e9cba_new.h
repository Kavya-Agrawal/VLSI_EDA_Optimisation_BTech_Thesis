// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68141497;
  double density_weight = 0.55943057;
  double prefix_weight = 0.42513789;
  double neighborhood_weight = 0.24710674;
  double late_weight = 0.13798393;
  double critical_weight = 0.30948613;
  unsigned budget = 7;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
