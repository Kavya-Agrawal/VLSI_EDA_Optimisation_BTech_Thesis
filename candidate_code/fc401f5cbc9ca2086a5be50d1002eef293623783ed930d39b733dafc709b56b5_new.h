// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68618363;
  double density_weight = 0.15576740;
  double prefix_weight = 0.01619493;
  double neighborhood_weight = 0.22327610;
  double late_weight = 0.09559770;
  double critical_weight = 0.09877243;
  unsigned budget = 32;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
