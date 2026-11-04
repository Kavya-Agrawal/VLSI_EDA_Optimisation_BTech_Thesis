// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21298289;
  double density_weight = 0.43491004;
  double prefix_weight = 0.43493614;
  double neighborhood_weight = 0.13937933;
  double late_weight = 0.16786975;
  double critical_weight = 0.25096236;
  unsigned budget = 25;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
