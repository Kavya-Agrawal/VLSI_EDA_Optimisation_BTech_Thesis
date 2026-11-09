// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05196370;
  double density_weight = 0.13308098;
  double prefix_weight = 0.29595485;
  double neighborhood_weight = 0.11504184;
  double late_weight = 0.28921120;
  double critical_weight = 0.36497209;
  unsigned budget = 29;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
