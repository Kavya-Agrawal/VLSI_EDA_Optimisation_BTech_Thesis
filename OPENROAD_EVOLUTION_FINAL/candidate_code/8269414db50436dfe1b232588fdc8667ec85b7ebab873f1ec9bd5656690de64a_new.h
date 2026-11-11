// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92204722;
  double density_weight = 0.21410194;
  double prefix_weight = 0.28548763;
  double neighborhood_weight = 0.37477526;
  double late_weight = 0.23207949;
  double critical_weight = 0.11846158;
  unsigned budget = 6;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
