// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98621278;
  double density_weight = 0.47611997;
  double prefix_weight = 0.23642608;
  double neighborhood_weight = 0.22143021;
  double late_weight = 0.18578449;
  double critical_weight = 0.37509068;
  unsigned budget = 31;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
