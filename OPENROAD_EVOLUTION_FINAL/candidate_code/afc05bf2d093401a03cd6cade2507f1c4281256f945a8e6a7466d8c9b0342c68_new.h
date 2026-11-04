// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10194745;
  double density_weight = 0.33808237;
  double prefix_weight = 0.31161938;
  double neighborhood_weight = 0.00853965;
  double late_weight = 0.02730478;
  double critical_weight = 0.08180985;
  unsigned budget = 22;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
