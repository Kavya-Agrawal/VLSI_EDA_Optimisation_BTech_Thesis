// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11692757;
  double density_weight = 0.56162023;
  double prefix_weight = 0.27839884;
  double neighborhood_weight = 0.17042805;
  double late_weight = 0.00048945;
  double critical_weight = 0.00424089;
  unsigned budget = 37;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
