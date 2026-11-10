// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02119782;
  double density_weight = 0.38945752;
  double prefix_weight = 0.07542402;
  double neighborhood_weight = 0.31781186;
  double late_weight = 0.04293104;
  double critical_weight = 0.16250342;
  unsigned budget = 10;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
