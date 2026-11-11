// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54187853;
  double density_weight = 0.33793629;
  double prefix_weight = 0.18638401;
  double neighborhood_weight = 0.31233170;
  double late_weight = 0.20000449;
  double critical_weight = 0.29267008;
  unsigned budget = 10;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
