// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41580905;
  double density_weight = 0.36614329;
  double prefix_weight = 0.12043308;
  double neighborhood_weight = 0.25343195;
  double late_weight = 0.17535785;
  double critical_weight = 0.41543895;
  unsigned budget = 12;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
