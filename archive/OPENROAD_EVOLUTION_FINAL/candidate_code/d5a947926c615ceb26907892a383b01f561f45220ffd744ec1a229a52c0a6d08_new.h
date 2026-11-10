// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48918259;
  double density_weight = 0.13550644;
  double prefix_weight = 0.39680739;
  double neighborhood_weight = 0.32897075;
  double late_weight = 0.27348015;
  double critical_weight = 0.23428434;
  unsigned budget = 17;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
