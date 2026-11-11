// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07898806;
  double density_weight = 0.29862778;
  double prefix_weight = 0.08720698;
  double neighborhood_weight = 0.22220988;
  double late_weight = 0.00992185;
  double critical_weight = 0.20911281;
  unsigned budget = 25;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
