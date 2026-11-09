// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21196700;
  double density_weight = 0.00874813;
  double prefix_weight = 0.42379461;
  double neighborhood_weight = 0.36028278;
  double late_weight = 0.00992647;
  double critical_weight = 0.48709632;
  unsigned budget = 14;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
