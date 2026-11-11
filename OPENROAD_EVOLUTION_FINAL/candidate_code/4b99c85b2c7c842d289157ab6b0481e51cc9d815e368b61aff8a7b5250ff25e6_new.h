// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66871923;
  double density_weight = 0.00014149;
  double prefix_weight = 0.13995455;
  double neighborhood_weight = 0.12259433;
  double late_weight = 0.12673943;
  double critical_weight = 0.43791885;
  unsigned budget = 25;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
