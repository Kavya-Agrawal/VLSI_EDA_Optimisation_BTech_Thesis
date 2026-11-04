// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31923214;
  double density_weight = 0.18510165;
  double prefix_weight = 0.44179811;
  double neighborhood_weight = 0.01468358;
  double late_weight = 0.24712516;
  double critical_weight = 0.44194887;
  unsigned budget = 22;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
