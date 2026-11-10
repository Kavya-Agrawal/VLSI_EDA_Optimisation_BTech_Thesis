// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98064369;
  double density_weight = 0.27033562;
  double prefix_weight = 0.12989062;
  double neighborhood_weight = 0.13387978;
  double late_weight = 0.29491315;
  double critical_weight = 0.36014490;
  unsigned budget = 29;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
