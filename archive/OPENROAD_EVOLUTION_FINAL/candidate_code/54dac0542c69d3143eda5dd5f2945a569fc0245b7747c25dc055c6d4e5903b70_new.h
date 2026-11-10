// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95751928;
  double density_weight = 0.37778912;
  double prefix_weight = 0.45433197;
  double neighborhood_weight = 0.00203697;
  double late_weight = 0.07376708;
  double critical_weight = 0.04147020;
  unsigned budget = 25;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
