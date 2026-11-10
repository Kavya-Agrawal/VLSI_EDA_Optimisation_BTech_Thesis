// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03644233;
  double density_weight = 0.00215219;
  double prefix_weight = 0.14126889;
  double neighborhood_weight = 0.18168756;
  double late_weight = 0.08261027;
  double critical_weight = 0.30778279;
  unsigned budget = 38;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
