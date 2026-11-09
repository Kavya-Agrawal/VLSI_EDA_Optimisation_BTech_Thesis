// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52377331;
  double density_weight = 0.45355504;
  double prefix_weight = 0.41932892;
  double neighborhood_weight = 0.07499547;
  double late_weight = 0.20432543;
  double critical_weight = 0.18247288;
  unsigned budget = 13;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
