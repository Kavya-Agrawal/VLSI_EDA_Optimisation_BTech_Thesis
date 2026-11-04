// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03765361;
  double density_weight = 0.23190163;
  double prefix_weight = 0.21265857;
  double neighborhood_weight = 0.14172695;
  double late_weight = 0.17262987;
  double critical_weight = 0.30313765;
  unsigned budget = 11;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
