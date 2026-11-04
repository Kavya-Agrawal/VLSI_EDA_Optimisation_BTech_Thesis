// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89713016;
  double density_weight = 0.03381330;
  double prefix_weight = 0.00385553;
  double neighborhood_weight = 0.36804181;
  double late_weight = 0.22208151;
  double critical_weight = 0.07004748;
  unsigned budget = 39;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
