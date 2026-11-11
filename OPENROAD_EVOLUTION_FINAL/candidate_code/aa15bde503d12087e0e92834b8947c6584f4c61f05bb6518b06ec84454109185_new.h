// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03122891;
  double density_weight = 0.00232349;
  double prefix_weight = 0.05518061;
  double neighborhood_weight = 0.38211077;
  double late_weight = 0.12863257;
  double critical_weight = 0.05798659;
  unsigned budget = 35;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
