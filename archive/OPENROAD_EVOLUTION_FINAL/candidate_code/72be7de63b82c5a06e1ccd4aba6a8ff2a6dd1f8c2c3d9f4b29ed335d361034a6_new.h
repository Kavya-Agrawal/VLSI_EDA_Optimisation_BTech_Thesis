// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05451319;
  double density_weight = 0.12922528;
  double prefix_weight = 0.06345206;
  double neighborhood_weight = 0.01374424;
  double late_weight = 0.12285666;
  double critical_weight = 0.24508358;
  unsigned budget = 30;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
