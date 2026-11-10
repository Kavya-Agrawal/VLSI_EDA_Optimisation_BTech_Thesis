// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47757820;
  double density_weight = 0.39482549;
  double prefix_weight = 0.16908407;
  double neighborhood_weight = 0.10684093;
  double late_weight = 0.16821668;
  double critical_weight = 0.21986679;
  unsigned budget = 9;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
