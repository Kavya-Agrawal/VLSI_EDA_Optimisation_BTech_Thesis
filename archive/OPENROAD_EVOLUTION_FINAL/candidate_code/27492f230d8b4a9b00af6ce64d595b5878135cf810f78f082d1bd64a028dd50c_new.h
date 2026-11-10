// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90950684;
  double density_weight = 0.23615954;
  double prefix_weight = 0.02756466;
  double neighborhood_weight = 0.01291573;
  double late_weight = 0.12120629;
  double critical_weight = 0.26010582;
  unsigned budget = 10;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
