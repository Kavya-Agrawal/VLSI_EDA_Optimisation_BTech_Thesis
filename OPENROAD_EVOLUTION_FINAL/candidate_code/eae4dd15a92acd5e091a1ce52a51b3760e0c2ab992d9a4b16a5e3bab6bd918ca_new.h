// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46223291;
  double density_weight = 0.30239866;
  double prefix_weight = 0.38112282;
  double neighborhood_weight = 0.07838525;
  double late_weight = 0.19614830;
  double critical_weight = 0.17447376;
  unsigned budget = 36;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
