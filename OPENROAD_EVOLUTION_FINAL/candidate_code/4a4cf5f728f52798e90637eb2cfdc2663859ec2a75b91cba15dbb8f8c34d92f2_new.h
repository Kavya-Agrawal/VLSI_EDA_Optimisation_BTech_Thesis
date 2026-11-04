// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82441625;
  double density_weight = 0.36632314;
  double prefix_weight = 0.10986302;
  double neighborhood_weight = 0.17386848;
  double late_weight = 0.28188697;
  double critical_weight = 0.10221792;
  unsigned budget = 40;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
