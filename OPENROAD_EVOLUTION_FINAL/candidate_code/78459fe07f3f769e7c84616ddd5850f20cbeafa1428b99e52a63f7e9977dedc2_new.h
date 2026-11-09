// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10797493;
  double density_weight = 0.19347103;
  double prefix_weight = 0.20875886;
  double neighborhood_weight = 0.33672581;
  double late_weight = 0.17990573;
  double critical_weight = 0.26577436;
  unsigned budget = 20;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
