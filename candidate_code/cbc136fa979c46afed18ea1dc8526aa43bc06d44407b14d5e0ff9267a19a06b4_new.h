// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42892869;
  double density_weight = 0.43658691;
  double prefix_weight = 0.12978816;
  double neighborhood_weight = 0.04411274;
  double late_weight = 0.27797054;
  double critical_weight = 0.31852341;
  unsigned budget = 34;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
