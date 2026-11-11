// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00744136;
  double density_weight = 0.18187928;
  double prefix_weight = 0.38480481;
  double neighborhood_weight = 0.30143605;
  double late_weight = 0.20151862;
  double critical_weight = 0.28907975;
  unsigned budget = 29;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
