// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04785373;
  double density_weight = 0.10377651;
  double prefix_weight = 0.23426928;
  double neighborhood_weight = 0.19558923;
  double late_weight = 0.26932432;
  double critical_weight = 0.38944877;
  unsigned budget = 25;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
