// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37575101;
  double density_weight = 0.19701240;
  double prefix_weight = 0.49298338;
  double neighborhood_weight = 0.36924944;
  double late_weight = 0.11301539;
  double critical_weight = 0.14101240;
  unsigned budget = 6;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
