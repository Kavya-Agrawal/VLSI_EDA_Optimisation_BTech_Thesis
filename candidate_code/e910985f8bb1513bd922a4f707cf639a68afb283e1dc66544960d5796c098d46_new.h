// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02075862;
  double density_weight = 0.27866751;
  double prefix_weight = 0.34215570;
  double neighborhood_weight = 0.17920600;
  double late_weight = 0.06021023;
  double critical_weight = 0.05314058;
  unsigned budget = 23;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
