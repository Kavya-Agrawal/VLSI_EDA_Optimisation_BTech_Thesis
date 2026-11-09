// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97693031;
  double density_weight = 0.08312751;
  double prefix_weight = 0.21331144;
  double neighborhood_weight = 0.28564805;
  double late_weight = 0.08882571;
  double critical_weight = 0.36653480;
  unsigned budget = 25;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
