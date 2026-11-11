// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59846169;
  double density_weight = 0.36177279;
  double prefix_weight = 0.41329721;
  double neighborhood_weight = 0.01709858;
  double late_weight = 0.20573067;
  double critical_weight = 0.14771732;
  unsigned budget = 37;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
