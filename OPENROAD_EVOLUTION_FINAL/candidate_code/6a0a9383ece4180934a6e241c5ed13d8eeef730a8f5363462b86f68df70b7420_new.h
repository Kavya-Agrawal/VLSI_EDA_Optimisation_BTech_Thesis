// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86295350;
  double density_weight = 0.24571161;
  double prefix_weight = 0.30833831;
  double neighborhood_weight = 0.35554619;
  double late_weight = 0.13131777;
  double critical_weight = 0.49447783;
  unsigned budget = 20;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
