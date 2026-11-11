// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82417339;
  double density_weight = 0.07965085;
  double prefix_weight = 0.30152206;
  double neighborhood_weight = 0.29997996;
  double late_weight = 0.09040322;
  double critical_weight = 0.07969218;
  unsigned budget = 16;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
