// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46752188;
  double density_weight = 0.20288886;
  double prefix_weight = 0.49955381;
  double neighborhood_weight = 0.31965230;
  double late_weight = 0.03518575;
  double critical_weight = 0.48287908;
  unsigned budget = 37;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
