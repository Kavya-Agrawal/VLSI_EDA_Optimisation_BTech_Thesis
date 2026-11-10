// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11559776;
  double density_weight = 0.48133731;
  double prefix_weight = 0.27909624;
  double neighborhood_weight = 0.14170896;
  double late_weight = 0.04468000;
  double critical_weight = 0.35943376;
  unsigned budget = 16;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
