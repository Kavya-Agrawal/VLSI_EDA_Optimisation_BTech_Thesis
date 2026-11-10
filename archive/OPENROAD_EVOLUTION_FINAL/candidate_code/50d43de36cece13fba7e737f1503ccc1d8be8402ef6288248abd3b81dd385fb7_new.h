// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35076170;
  double density_weight = 0.21580310;
  double prefix_weight = 0.36527700;
  double neighborhood_weight = 0.26851810;
  double late_weight = 0.15597109;
  double critical_weight = 0.25029676;
  unsigned budget = 9;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
