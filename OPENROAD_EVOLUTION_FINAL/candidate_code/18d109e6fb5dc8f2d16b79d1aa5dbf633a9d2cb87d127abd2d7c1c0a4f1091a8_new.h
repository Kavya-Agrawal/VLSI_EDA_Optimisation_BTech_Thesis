// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61557410;
  double density_weight = 0.06133084;
  double prefix_weight = 0.17759974;
  double neighborhood_weight = 0.21831270;
  double late_weight = 0.17312027;
  double critical_weight = 0.00766747;
  unsigned budget = 13;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
