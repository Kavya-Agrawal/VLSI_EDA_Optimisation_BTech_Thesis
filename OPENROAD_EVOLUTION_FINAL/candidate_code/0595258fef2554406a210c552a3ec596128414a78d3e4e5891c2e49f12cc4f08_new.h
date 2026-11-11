// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93202848;
  double density_weight = 0.29056573;
  double prefix_weight = 0.37297102;
  double neighborhood_weight = 0.19720004;
  double late_weight = 0.18158316;
  double critical_weight = 0.25062064;
  unsigned budget = 30;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
