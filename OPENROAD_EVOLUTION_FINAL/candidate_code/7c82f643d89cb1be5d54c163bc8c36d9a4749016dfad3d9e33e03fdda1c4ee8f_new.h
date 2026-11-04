// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61153968;
  double density_weight = 0.58231033;
  double prefix_weight = 0.03386301;
  double neighborhood_weight = 0.07302839;
  double late_weight = 0.21515193;
  double critical_weight = 0.27755083;
  unsigned budget = 38;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
