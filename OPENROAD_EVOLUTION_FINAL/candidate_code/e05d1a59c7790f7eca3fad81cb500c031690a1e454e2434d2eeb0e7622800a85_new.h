// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67655731;
  double density_weight = 0.43439370;
  double prefix_weight = 0.49956184;
  double neighborhood_weight = 0.15749381;
  double late_weight = 0.23249500;
  double critical_weight = 0.05161559;
  unsigned budget = 20;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
