// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30454345;
  double density_weight = 0.37540622;
  double prefix_weight = 0.02407990;
  double neighborhood_weight = 0.29679545;
  double late_weight = 0.29521102;
  double critical_weight = 0.19767994;
  unsigned budget = 17;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
