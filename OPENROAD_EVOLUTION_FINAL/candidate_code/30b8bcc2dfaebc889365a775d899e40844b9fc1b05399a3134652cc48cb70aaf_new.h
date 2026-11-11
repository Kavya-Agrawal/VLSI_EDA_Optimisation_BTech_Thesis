// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64615612;
  double density_weight = 0.04102237;
  double prefix_weight = 0.35420022;
  double neighborhood_weight = 0.28593226;
  double late_weight = 0.06301546;
  double critical_weight = 0.28820874;
  unsigned budget = 22;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
