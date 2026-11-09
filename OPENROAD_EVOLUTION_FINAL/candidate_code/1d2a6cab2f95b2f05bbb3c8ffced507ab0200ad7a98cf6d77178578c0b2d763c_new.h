// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76390755;
  double density_weight = 0.51920022;
  double prefix_weight = 0.22396711;
  double neighborhood_weight = 0.00269567;
  double late_weight = 0.03080101;
  double critical_weight = 0.00098432;
  unsigned budget = 40;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
