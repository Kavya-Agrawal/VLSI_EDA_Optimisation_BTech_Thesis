// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33595053;
  double density_weight = 0.34917428;
  double prefix_weight = 0.26937443;
  double neighborhood_weight = 0.25336257;
  double late_weight = 0.13336330;
  double critical_weight = 0.37524295;
  unsigned budget = 11;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
