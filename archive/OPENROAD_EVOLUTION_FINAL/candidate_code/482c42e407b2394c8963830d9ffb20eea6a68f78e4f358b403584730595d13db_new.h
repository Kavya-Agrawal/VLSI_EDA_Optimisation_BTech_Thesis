// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38502271;
  double density_weight = 0.45149433;
  double prefix_weight = 0.21034677;
  double neighborhood_weight = 0.04021387;
  double late_weight = 0.20052072;
  double critical_weight = 0.45211303;
  unsigned budget = 34;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
