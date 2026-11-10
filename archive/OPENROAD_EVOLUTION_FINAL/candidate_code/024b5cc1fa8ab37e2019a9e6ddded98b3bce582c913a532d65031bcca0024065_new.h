// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62377329;
  double density_weight = 0.03988094;
  double prefix_weight = 0.47746985;
  double neighborhood_weight = 0.22307883;
  double late_weight = 0.26238166;
  double critical_weight = 0.49848987;
  unsigned budget = 20;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
