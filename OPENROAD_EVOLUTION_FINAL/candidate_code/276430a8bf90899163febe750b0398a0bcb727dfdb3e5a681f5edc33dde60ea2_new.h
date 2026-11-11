// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72601275;
  double density_weight = 0.14157876;
  double prefix_weight = 0.19572541;
  double neighborhood_weight = 0.01853180;
  double late_weight = 0.15067349;
  double critical_weight = 0.45619805;
  unsigned budget = 21;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
