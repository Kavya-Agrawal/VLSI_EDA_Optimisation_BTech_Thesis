// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34234244;
  double density_weight = 0.07181025;
  double prefix_weight = 0.10057810;
  double neighborhood_weight = 0.08098069;
  double late_weight = 0.04897396;
  double critical_weight = 0.02888116;
  unsigned budget = 5;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
