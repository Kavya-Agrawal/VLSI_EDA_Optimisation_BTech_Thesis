// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78856072;
  double density_weight = 0.57548043;
  double prefix_weight = 0.15743576;
  double neighborhood_weight = 0.10983952;
  double late_weight = 0.12182574;
  double critical_weight = 0.05815843;
  unsigned budget = 28;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
