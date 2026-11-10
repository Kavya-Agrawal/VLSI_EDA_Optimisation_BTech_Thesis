// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86097360;
  double density_weight = 0.26322369;
  double prefix_weight = 0.26922989;
  double neighborhood_weight = 0.37937437;
  double late_weight = 0.23692212;
  double critical_weight = 0.41997853;
  unsigned budget = 5;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
