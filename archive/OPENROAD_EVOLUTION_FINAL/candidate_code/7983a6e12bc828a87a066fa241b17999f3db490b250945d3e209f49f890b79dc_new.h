// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06052396;
  double density_weight = 0.15283361;
  double prefix_weight = 0.02812667;
  double neighborhood_weight = 0.29434618;
  double late_weight = 0.10553023;
  double critical_weight = 0.14226449;
  unsigned budget = 27;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
