// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27764113;
  double density_weight = 0.24830535;
  double prefix_weight = 0.33343568;
  double neighborhood_weight = 0.09594643;
  double late_weight = 0.21505864;
  double critical_weight = 0.47063557;
  unsigned budget = 10;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
