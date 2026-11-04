// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46764405;
  double density_weight = 0.04304155;
  double prefix_weight = 0.39734048;
  double neighborhood_weight = 0.11178088;
  double late_weight = 0.07005698;
  double critical_weight = 0.32306026;
  unsigned budget = 19;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
