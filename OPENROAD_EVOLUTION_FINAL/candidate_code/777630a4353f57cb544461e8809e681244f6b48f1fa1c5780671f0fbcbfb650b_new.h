// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48074761;
  double density_weight = 0.56731054;
  double prefix_weight = 0.10467523;
  double neighborhood_weight = 0.09275158;
  double late_weight = 0.09244844;
  double critical_weight = 0.34706916;
  unsigned budget = 4;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
