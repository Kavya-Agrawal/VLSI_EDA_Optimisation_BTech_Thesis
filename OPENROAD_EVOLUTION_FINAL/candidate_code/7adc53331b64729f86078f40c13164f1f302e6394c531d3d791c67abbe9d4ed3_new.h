// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25749378;
  double density_weight = 0.20230418;
  double prefix_weight = 0.45195707;
  double neighborhood_weight = 0.30967775;
  double late_weight = 0.07380644;
  double critical_weight = 0.01184348;
  unsigned budget = 19;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
