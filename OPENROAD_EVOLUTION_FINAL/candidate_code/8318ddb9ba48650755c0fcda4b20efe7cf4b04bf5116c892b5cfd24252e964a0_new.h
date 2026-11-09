// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09823414;
  double density_weight = 0.35394795;
  double prefix_weight = 0.27603164;
  double neighborhood_weight = 0.23544625;
  double late_weight = 0.06770650;
  double critical_weight = 0.00958746;
  unsigned budget = 13;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
