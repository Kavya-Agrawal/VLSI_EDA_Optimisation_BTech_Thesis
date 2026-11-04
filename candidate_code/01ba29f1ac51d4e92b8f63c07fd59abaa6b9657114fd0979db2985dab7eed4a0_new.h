// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08691544;
  double density_weight = 0.49733982;
  double prefix_weight = 0.27201882;
  double neighborhood_weight = 0.24918545;
  double late_weight = 0.17154636;
  double critical_weight = 0.31823796;
  unsigned budget = 4;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
