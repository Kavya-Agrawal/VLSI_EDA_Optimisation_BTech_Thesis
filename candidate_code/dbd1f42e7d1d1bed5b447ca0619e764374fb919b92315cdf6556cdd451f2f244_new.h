// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22901394;
  double density_weight = 0.37776867;
  double prefix_weight = 0.46708527;
  double neighborhood_weight = 0.34658613;
  double late_weight = 0.04428795;
  double critical_weight = 0.35003420;
  unsigned budget = 13;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
