// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86036201;
  double density_weight = 0.50029741;
  double prefix_weight = 0.22061001;
  double neighborhood_weight = 0.12049651;
  double late_weight = 0.25123190;
  double critical_weight = 0.32358843;
  unsigned budget = 15;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
