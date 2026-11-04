// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58082578;
  double density_weight = 0.20588807;
  double prefix_weight = 0.33359428;
  double neighborhood_weight = 0.00612016;
  double late_weight = 0.21251794;
  double critical_weight = 0.45331605;
  unsigned budget = 39;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
