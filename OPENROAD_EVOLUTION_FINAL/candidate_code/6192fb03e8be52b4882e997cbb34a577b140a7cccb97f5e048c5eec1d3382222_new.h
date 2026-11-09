// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08022990;
  double density_weight = 0.41477681;
  double prefix_weight = 0.10797469;
  double neighborhood_weight = 0.38733427;
  double late_weight = 0.18637249;
  double critical_weight = 0.47097756;
  unsigned budget = 10;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
