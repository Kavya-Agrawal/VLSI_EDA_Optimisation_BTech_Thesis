// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29153927;
  double density_weight = 0.49022520;
  double prefix_weight = 0.32596065;
  double neighborhood_weight = 0.03961266;
  double late_weight = 0.15492036;
  double critical_weight = 0.23682287;
  unsigned budget = 26;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
