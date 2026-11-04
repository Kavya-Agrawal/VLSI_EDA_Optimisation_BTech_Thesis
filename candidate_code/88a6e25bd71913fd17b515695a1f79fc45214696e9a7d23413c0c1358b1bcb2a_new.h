// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80537217;
  double density_weight = 0.15664854;
  double prefix_weight = 0.13029319;
  double neighborhood_weight = 0.00546582;
  double late_weight = 0.00568068;
  double critical_weight = 0.34510204;
  unsigned budget = 10;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
