// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63968824;
  double density_weight = 0.42152152;
  double prefix_weight = 0.38502497;
  double neighborhood_weight = 0.08839955;
  double late_weight = 0.04370840;
  double critical_weight = 0.14490617;
  unsigned budget = 36;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
