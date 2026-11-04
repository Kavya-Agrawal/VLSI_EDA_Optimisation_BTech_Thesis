// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48892109;
  double density_weight = 0.21482044;
  double prefix_weight = 0.17728563;
  double neighborhood_weight = 0.38502288;
  double late_weight = 0.13578647;
  double critical_weight = 0.10863025;
  unsigned budget = 32;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
