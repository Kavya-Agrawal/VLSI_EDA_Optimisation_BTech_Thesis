// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60316097;
  double density_weight = 0.39047024;
  double prefix_weight = 0.25047621;
  double neighborhood_weight = 0.16850863;
  double late_weight = 0.06708016;
  double critical_weight = 0.45466226;
  unsigned budget = 18;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
