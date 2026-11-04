// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16031950;
  double density_weight = 0.56527358;
  double prefix_weight = 0.26038411;
  double neighborhood_weight = 0.09167039;
  double late_weight = 0.07699856;
  double critical_weight = 0.12530648;
  unsigned budget = 39;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
