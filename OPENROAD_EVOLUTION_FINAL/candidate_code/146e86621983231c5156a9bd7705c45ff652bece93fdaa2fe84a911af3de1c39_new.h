// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95811272;
  double density_weight = 0.30522452;
  double prefix_weight = 0.17902382;
  double neighborhood_weight = 0.01889947;
  double late_weight = 0.10809257;
  double critical_weight = 0.04667552;
  unsigned budget = 25;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
