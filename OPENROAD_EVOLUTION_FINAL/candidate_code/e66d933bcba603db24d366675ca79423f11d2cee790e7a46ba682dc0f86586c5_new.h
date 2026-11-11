// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66197542;
  double density_weight = 0.04403858;
  double prefix_weight = 0.15644580;
  double neighborhood_weight = 0.09031714;
  double late_weight = 0.14925301;
  double critical_weight = 0.22636181;
  unsigned budget = 14;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
