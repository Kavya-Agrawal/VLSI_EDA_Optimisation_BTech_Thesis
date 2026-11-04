// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57653285;
  double density_weight = 0.14652688;
  double prefix_weight = 0.43096385;
  double neighborhood_weight = 0.33332406;
  double late_weight = 0.18713032;
  double critical_weight = 0.40858999;
  unsigned budget = 27;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
