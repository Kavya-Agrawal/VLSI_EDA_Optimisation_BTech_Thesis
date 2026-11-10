// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11105886;
  double density_weight = 0.14011269;
  double prefix_weight = 0.05763128;
  double neighborhood_weight = 0.18572142;
  double late_weight = 0.25236529;
  double critical_weight = 0.14343303;
  unsigned budget = 24;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
