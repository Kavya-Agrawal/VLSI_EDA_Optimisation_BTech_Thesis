// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86951587;
  double density_weight = 0.18270928;
  double prefix_weight = 0.02451817;
  double neighborhood_weight = 0.04712951;
  double late_weight = 0.01113374;
  double critical_weight = 0.12956131;
  unsigned budget = 9;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
