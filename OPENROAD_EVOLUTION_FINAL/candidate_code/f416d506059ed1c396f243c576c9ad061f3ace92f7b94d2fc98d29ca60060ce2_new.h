// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51916335;
  double density_weight = 0.08394829;
  double prefix_weight = 0.28817585;
  double neighborhood_weight = 0.24368750;
  double late_weight = 0.29945866;
  double critical_weight = 0.17666434;
  unsigned budget = 24;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
