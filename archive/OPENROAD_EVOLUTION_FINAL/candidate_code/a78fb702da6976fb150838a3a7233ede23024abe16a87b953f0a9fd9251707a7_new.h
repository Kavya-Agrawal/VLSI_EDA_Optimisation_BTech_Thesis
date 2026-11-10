// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71728533;
  double density_weight = 0.23265505;
  double prefix_weight = 0.36944553;
  double neighborhood_weight = 0.13568072;
  double late_weight = 0.21312659;
  double critical_weight = 0.00377231;
  unsigned budget = 4;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
