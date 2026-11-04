// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34782400;
  double density_weight = 0.10293010;
  double prefix_weight = 0.19108959;
  double neighborhood_weight = 0.24061330;
  double late_weight = 0.02992522;
  double critical_weight = 0.23996116;
  unsigned budget = 7;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
