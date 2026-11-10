// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90036865;
  double density_weight = 0.19646857;
  double prefix_weight = 0.02388995;
  double neighborhood_weight = 0.38448007;
  double late_weight = 0.06616086;
  double critical_weight = 0.21730194;
  unsigned budget = 38;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
