// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40005679;
  double density_weight = 0.17922916;
  double prefix_weight = 0.22491587;
  double neighborhood_weight = 0.05756013;
  double late_weight = 0.18591589;
  double critical_weight = 0.35894312;
  unsigned budget = 6;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
