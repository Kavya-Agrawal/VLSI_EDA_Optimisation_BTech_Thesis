// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24569146;
  double density_weight = 0.43651297;
  double prefix_weight = 0.17332978;
  double neighborhood_weight = 0.15641980;
  double late_weight = 0.29429066;
  double critical_weight = 0.02287809;
  unsigned budget = 10;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
