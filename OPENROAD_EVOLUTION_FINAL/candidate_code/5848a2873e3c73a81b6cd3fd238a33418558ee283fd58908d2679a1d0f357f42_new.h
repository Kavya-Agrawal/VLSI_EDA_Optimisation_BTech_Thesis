// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87546338;
  double density_weight = 0.11643274;
  double prefix_weight = 0.19465340;
  double neighborhood_weight = 0.11118598;
  double late_weight = 0.02537979;
  double critical_weight = 0.45686778;
  unsigned budget = 8;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
