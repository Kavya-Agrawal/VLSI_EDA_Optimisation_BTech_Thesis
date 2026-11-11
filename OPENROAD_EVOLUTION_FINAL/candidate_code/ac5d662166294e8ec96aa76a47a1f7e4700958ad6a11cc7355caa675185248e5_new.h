// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76623063;
  double density_weight = 0.00504123;
  double prefix_weight = 0.41142037;
  double neighborhood_weight = 0.05633792;
  double late_weight = 0.21279110;
  double critical_weight = 0.07375741;
  unsigned budget = 18;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
