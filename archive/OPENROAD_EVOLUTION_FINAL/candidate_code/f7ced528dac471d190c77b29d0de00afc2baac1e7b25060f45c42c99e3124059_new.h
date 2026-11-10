// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62977610;
  double density_weight = 0.28729178;
  double prefix_weight = 0.25880788;
  double neighborhood_weight = 0.15627809;
  double late_weight = 0.15917671;
  double critical_weight = 0.18392882;
  unsigned budget = 40;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
