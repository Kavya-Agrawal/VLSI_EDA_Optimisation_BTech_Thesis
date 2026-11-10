// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95632615;
  double density_weight = 0.38091122;
  double prefix_weight = 0.09865828;
  double neighborhood_weight = 0.19475922;
  double late_weight = 0.11199562;
  double critical_weight = 0.35220445;
  unsigned budget = 32;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
