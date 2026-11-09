// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52775972;
  double density_weight = 0.29919847;
  double prefix_weight = 0.03465447;
  double neighborhood_weight = 0.29267623;
  double late_weight = 0.06004061;
  double critical_weight = 0.31061623;
  unsigned budget = 29;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
