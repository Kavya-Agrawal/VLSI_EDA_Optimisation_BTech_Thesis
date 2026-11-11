// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85355379;
  double density_weight = 0.48035507;
  double prefix_weight = 0.21445186;
  double neighborhood_weight = 0.31394827;
  double late_weight = 0.23276763;
  double critical_weight = 0.15747119;
  unsigned budget = 34;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
