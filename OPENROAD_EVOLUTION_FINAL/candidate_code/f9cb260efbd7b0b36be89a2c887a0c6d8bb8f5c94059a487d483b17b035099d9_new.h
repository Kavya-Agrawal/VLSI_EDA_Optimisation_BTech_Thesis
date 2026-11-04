// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43420117;
  double density_weight = 0.13168671;
  double prefix_weight = 0.42046315;
  double neighborhood_weight = 0.36075540;
  double late_weight = 0.27221632;
  double critical_weight = 0.33795423;
  unsigned budget = 23;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
