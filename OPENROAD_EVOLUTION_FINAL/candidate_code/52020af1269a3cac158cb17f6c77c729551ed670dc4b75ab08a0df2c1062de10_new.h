// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54993664;
  double density_weight = 0.48939131;
  double prefix_weight = 0.46898809;
  double neighborhood_weight = 0.38790604;
  double late_weight = 0.24949080;
  double critical_weight = 0.29987770;
  unsigned budget = 18;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
