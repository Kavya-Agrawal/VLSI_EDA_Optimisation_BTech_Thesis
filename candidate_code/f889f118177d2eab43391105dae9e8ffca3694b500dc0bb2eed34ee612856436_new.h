// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22997004;
  double density_weight = 0.29078439;
  double prefix_weight = 0.41647451;
  double neighborhood_weight = 0.06791424;
  double late_weight = 0.20574284;
  double critical_weight = 0.06823357;
  unsigned budget = 26;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
