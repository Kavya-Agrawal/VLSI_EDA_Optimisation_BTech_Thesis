// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51689074;
  double density_weight = 0.11466373;
  double prefix_weight = 0.11370936;
  double neighborhood_weight = 0.16967873;
  double late_weight = 0.18122551;
  double critical_weight = 0.39280326;
  unsigned budget = 29;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
