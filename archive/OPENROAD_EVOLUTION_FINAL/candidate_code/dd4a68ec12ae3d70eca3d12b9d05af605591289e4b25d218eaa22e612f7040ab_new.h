// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16001430;
  double density_weight = 0.58448309;
  double prefix_weight = 0.44144803;
  double neighborhood_weight = 0.04034439;
  double late_weight = 0.13803812;
  double critical_weight = 0.02980235;
  unsigned budget = 26;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
