// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55440269;
  double density_weight = 0.39036844;
  double prefix_weight = 0.08005180;
  double neighborhood_weight = 0.01587183;
  double late_weight = 0.20013711;
  double critical_weight = 0.37261414;
  unsigned budget = 20;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
