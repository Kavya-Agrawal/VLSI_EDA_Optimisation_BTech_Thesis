// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71780874;
  double density_weight = 0.58666379;
  double prefix_weight = 0.16063457;
  double neighborhood_weight = 0.00598936;
  double late_weight = 0.16364781;
  double critical_weight = 0.25553891;
  unsigned budget = 15;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
