// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82102946;
  double density_weight = 0.57943408;
  double prefix_weight = 0.42370072;
  double neighborhood_weight = 0.35687200;
  double late_weight = 0.16461247;
  double critical_weight = 0.15040077;
  unsigned budget = 5;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
