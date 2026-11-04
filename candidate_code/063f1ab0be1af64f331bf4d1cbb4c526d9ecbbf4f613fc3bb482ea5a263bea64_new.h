// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93571761;
  double density_weight = 0.33118549;
  double prefix_weight = 0.48514857;
  double neighborhood_weight = 0.31155984;
  double late_weight = 0.09352604;
  double critical_weight = 0.26989558;
  unsigned budget = 17;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
