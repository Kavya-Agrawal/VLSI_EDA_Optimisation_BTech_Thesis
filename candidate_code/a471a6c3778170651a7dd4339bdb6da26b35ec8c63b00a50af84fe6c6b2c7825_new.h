// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79168506;
  double density_weight = 0.46603733;
  double prefix_weight = 0.17152773;
  double neighborhood_weight = 0.36632932;
  double late_weight = 0.25297912;
  double critical_weight = 0.34745820;
  unsigned budget = 30;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
