// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13752195;
  double density_weight = 0.07365091;
  double prefix_weight = 0.45767178;
  double neighborhood_weight = 0.18992330;
  double late_weight = 0.19732825;
  double critical_weight = 0.49432773;
  unsigned budget = 10;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
