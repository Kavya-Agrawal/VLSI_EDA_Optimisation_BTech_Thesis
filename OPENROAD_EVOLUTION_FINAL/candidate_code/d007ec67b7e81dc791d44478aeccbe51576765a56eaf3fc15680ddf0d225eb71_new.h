// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81640322;
  double density_weight = 0.00810206;
  double prefix_weight = 0.26368738;
  double neighborhood_weight = 0.35158309;
  double late_weight = 0.17863404;
  double critical_weight = 0.23377241;
  unsigned budget = 26;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
