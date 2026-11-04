// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52877569;
  double density_weight = 0.50040525;
  double prefix_weight = 0.46964755;
  double neighborhood_weight = 0.13177319;
  double late_weight = 0.09852943;
  double critical_weight = 0.42269658;
  unsigned budget = 14;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
