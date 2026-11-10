// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84049936;
  double density_weight = 0.49932795;
  double prefix_weight = 0.26855611;
  double neighborhood_weight = 0.10161190;
  double late_weight = 0.15722806;
  double critical_weight = 0.46373697;
  unsigned budget = 18;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
