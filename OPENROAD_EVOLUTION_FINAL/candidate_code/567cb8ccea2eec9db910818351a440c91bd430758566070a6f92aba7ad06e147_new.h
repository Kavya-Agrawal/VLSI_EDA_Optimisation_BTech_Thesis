// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42699955;
  double density_weight = 0.43958881;
  double prefix_weight = 0.15517797;
  double neighborhood_weight = 0.26266978;
  double late_weight = 0.20530229;
  double critical_weight = 0.26109994;
  unsigned budget = 28;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
