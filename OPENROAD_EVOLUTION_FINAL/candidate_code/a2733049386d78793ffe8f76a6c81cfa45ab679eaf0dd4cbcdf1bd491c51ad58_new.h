// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37768093;
  double density_weight = 0.41537819;
  double prefix_weight = 0.48640472;
  double neighborhood_weight = 0.13267751;
  double late_weight = 0.17090042;
  double critical_weight = 0.48720582;
  unsigned budget = 20;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
