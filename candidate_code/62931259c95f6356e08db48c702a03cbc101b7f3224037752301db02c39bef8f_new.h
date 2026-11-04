// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71127930;
  double density_weight = 0.56736612;
  double prefix_weight = 0.26573365;
  double neighborhood_weight = 0.09386095;
  double late_weight = 0.19306641;
  double critical_weight = 0.12832533;
  unsigned budget = 21;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
