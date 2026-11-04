// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10929113;
  double density_weight = 0.34517899;
  double prefix_weight = 0.27589887;
  double neighborhood_weight = 0.18345504;
  double late_weight = 0.17045235;
  double critical_weight = 0.30569097;
  unsigned budget = 10;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
