// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22334118;
  double density_weight = 0.31754674;
  double prefix_weight = 0.28536473;
  double neighborhood_weight = 0.15456129;
  double late_weight = 0.28283929;
  double critical_weight = 0.13495825;
  unsigned budget = 21;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
