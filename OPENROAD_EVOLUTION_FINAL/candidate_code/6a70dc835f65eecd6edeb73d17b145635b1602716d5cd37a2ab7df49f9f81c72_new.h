// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12910711;
  double density_weight = 0.19608895;
  double prefix_weight = 0.05629932;
  double neighborhood_weight = 0.25578170;
  double late_weight = 0.26874336;
  double critical_weight = 0.02893475;
  unsigned budget = 39;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
