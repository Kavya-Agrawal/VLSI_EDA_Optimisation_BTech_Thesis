// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83183616;
  double density_weight = 0.02496934;
  double prefix_weight = 0.06328358;
  double neighborhood_weight = 0.20531881;
  double late_weight = 0.23727623;
  double critical_weight = 0.46149315;
  unsigned budget = 22;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
