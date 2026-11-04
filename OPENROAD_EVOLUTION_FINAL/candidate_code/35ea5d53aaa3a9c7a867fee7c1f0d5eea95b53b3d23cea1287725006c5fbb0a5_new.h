// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38141036;
  double density_weight = 0.45112054;
  double prefix_weight = 0.19742445;
  double neighborhood_weight = 0.24847609;
  double late_weight = 0.16306244;
  double critical_weight = 0.38495090;
  unsigned budget = 21;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
