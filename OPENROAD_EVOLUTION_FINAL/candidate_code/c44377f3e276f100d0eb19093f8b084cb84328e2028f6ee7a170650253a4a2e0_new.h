// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22222260;
  double density_weight = 0.01811735;
  double prefix_weight = 0.45539930;
  double neighborhood_weight = 0.37042736;
  double late_weight = 0.09773476;
  double critical_weight = 0.03187978;
  unsigned budget = 23;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
