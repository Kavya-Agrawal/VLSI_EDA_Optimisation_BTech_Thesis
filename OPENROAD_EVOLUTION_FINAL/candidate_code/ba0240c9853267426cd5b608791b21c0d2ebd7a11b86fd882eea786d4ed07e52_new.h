// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99400493;
  double density_weight = 0.16900421;
  double prefix_weight = 0.45496824;
  double neighborhood_weight = 0.24747980;
  double late_weight = 0.27522694;
  double critical_weight = 0.24071301;
  unsigned budget = 6;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
