// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32010808;
  double density_weight = 0.59034020;
  double prefix_weight = 0.42186058;
  double neighborhood_weight = 0.18640205;
  double late_weight = 0.24440115;
  double critical_weight = 0.21188783;
  unsigned budget = 5;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
