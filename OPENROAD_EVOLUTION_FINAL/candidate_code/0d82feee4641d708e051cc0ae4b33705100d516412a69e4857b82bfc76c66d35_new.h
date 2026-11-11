// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04857351;
  double density_weight = 0.42843591;
  double prefix_weight = 0.48088891;
  double neighborhood_weight = 0.26720653;
  double late_weight = 0.24197516;
  double critical_weight = 0.24201889;
  unsigned budget = 26;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
