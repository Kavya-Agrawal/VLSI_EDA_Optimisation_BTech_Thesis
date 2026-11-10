// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11878423;
  double density_weight = 0.21119296;
  double prefix_weight = 0.00443741;
  double neighborhood_weight = 0.12997579;
  double late_weight = 0.24488127;
  double critical_weight = 0.43051506;
  unsigned budget = 17;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
