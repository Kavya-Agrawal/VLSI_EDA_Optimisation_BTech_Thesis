// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87899017;
  double density_weight = 0.57353482;
  double prefix_weight = 0.18041377;
  double neighborhood_weight = 0.00252775;
  double late_weight = 0.29700141;
  double critical_weight = 0.07682116;
  unsigned budget = 31;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
