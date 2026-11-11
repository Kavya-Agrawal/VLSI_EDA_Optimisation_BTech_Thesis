// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99681919;
  double density_weight = 0.29121715;
  double prefix_weight = 0.43660853;
  double neighborhood_weight = 0.30888787;
  double late_weight = 0.11525102;
  double critical_weight = 0.22652024;
  unsigned budget = 12;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
