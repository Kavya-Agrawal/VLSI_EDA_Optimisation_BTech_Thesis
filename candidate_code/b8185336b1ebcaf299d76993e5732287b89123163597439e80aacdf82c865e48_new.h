// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08197299;
  double density_weight = 0.59189724;
  double prefix_weight = 0.34940657;
  double neighborhood_weight = 0.22011684;
  double late_weight = 0.29902783;
  double critical_weight = 0.43249418;
  unsigned budget = 12;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
