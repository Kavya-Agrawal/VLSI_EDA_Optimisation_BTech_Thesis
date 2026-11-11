// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28092617;
  double density_weight = 0.49485184;
  double prefix_weight = 0.48636870;
  double neighborhood_weight = 0.08262012;
  double late_weight = 0.20265551;
  double critical_weight = 0.48851392;
  unsigned budget = 31;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
