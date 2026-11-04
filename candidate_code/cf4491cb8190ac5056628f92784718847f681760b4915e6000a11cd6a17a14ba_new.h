// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22107508;
  double density_weight = 0.48101530;
  double prefix_weight = 0.13451357;
  double neighborhood_weight = 0.25998751;
  double late_weight = 0.09722941;
  double critical_weight = 0.33858387;
  unsigned budget = 37;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
