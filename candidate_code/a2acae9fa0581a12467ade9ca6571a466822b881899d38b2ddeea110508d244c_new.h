// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80018874;
  double density_weight = 0.55359680;
  double prefix_weight = 0.12198033;
  double neighborhood_weight = 0.25648418;
  double late_weight = 0.24871179;
  double critical_weight = 0.36824326;
  unsigned budget = 10;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
