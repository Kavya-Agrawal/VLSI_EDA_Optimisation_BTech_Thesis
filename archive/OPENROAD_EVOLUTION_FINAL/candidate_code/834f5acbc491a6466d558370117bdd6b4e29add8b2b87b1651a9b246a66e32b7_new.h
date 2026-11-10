// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40206923;
  double density_weight = 0.30229597;
  double prefix_weight = 0.44531595;
  double neighborhood_weight = 0.28625804;
  double late_weight = 0.09004891;
  double critical_weight = 0.21460700;
  unsigned budget = 23;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
