// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20356264;
  double density_weight = 0.34002955;
  double prefix_weight = 0.19703122;
  double neighborhood_weight = 0.31833999;
  double late_weight = 0.19981227;
  double critical_weight = 0.02392567;
  unsigned budget = 24;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
