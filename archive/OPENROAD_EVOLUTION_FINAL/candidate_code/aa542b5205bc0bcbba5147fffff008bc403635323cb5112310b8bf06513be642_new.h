// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37062777;
  double density_weight = 0.34868196;
  double prefix_weight = 0.15781088;
  double neighborhood_weight = 0.24636117;
  double late_weight = 0.00820503;
  double critical_weight = 0.01161248;
  unsigned budget = 9;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
