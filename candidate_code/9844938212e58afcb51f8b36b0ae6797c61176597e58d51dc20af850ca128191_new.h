// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87722777;
  double density_weight = 0.31449045;
  double prefix_weight = 0.48093697;
  double neighborhood_weight = 0.00624460;
  double late_weight = 0.22760653;
  double critical_weight = 0.36054196;
  unsigned budget = 9;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
