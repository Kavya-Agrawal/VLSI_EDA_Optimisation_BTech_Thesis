// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90353394;
  double density_weight = 0.04681948;
  double prefix_weight = 0.10500942;
  double neighborhood_weight = 0.38751940;
  double late_weight = 0.03223065;
  double critical_weight = 0.04800626;
  unsigned budget = 31;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
