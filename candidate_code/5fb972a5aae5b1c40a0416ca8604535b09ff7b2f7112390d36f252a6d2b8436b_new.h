// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23749837;
  double density_weight = 0.51472360;
  double prefix_weight = 0.45461137;
  double neighborhood_weight = 0.36270990;
  double late_weight = 0.11884040;
  double critical_weight = 0.28855993;
  unsigned budget = 5;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
