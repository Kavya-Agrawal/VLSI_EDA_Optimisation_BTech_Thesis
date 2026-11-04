// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07251719;
  double density_weight = 0.17669856;
  double prefix_weight = 0.09174677;
  double neighborhood_weight = 0.33854850;
  double late_weight = 0.13232188;
  double critical_weight = 0.38719994;
  unsigned budget = 6;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
