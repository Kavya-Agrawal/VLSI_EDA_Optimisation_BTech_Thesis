// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09893410;
  double density_weight = 0.48983151;
  double prefix_weight = 0.45558801;
  double neighborhood_weight = 0.30352829;
  double late_weight = 0.24192772;
  double critical_weight = 0.21551682;
  unsigned budget = 37;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
