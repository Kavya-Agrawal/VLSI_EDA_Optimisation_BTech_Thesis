// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15400280;
  double density_weight = 0.33027413;
  double prefix_weight = 0.48864926;
  double neighborhood_weight = 0.04408689;
  double late_weight = 0.26389811;
  double critical_weight = 0.13537817;
  unsigned budget = 27;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
