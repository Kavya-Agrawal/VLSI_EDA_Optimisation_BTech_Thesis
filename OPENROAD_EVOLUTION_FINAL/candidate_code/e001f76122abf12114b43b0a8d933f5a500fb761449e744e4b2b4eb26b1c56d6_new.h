// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93923045;
  double density_weight = 0.47761853;
  double prefix_weight = 0.25851109;
  double neighborhood_weight = 0.10661114;
  double late_weight = 0.06196138;
  double critical_weight = 0.48633001;
  unsigned budget = 33;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
